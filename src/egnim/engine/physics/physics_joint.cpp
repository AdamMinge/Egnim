/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_joint.h>
#include <egnim/engine/physics/physics_body.h>
#include <egnim/engine/physics/physics_world.h>
#include <egnim/engine/physics/priv/physics_helper.h>
#include <egnim/engine/scene/scene_node.h>
#include <egnim/engine/scene/scene_visitor.h>
#include <egnim/engine/math/vector_helper.h>
/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_distance_joint.h>
#include <box2d/b2_friction_joint.h>
#include <box2d/b2_motor_joint.h>
#include <box2d/b2_prismatic_joint.h>
#include <box2d/b2_pulley_joint.h>
#include <box2d/b2_revolute_joint.h>
#include <box2d/b2_weld_joint.h>
#include <box2d/b2_wheel_joint.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics
{

#define PushPostProcessProperties(b2JointType, Setter, value, postprocess_value, properties)            \
do {                                                                                                    \
  if(auto joint = getInternalJoint<b2JointType>(); joint)                                               \
    { joint->Setter(postprocess_value); }                                                               \
  else                                                                                                  \
  { (properties) = value; }                                                                             \
                                                                                                        \
} while(false)

#define PushProperties(b2JointType, Setter, value, properties)                                          \
PushPostProcessProperties(b2JointType, Setter, value, value, properties)

#define PullProperties(b2JointType, Getter, properties)                                                 \
do {                                                                                                    \
  if(auto joint = getInternalJoint<b2JointType>(); joint)                                               \
    { return joint->Getter(); }                                                                         \
  else                                                                                                  \
    { return properties; }                                                                              \
} while(false)

#define PullPostProcessProperties(b2JointType, Getter, properties, postprocess)                         \
do {                                                                                                    \
  if(auto joint = getInternalJoint<b2JointType>(); joint)                                               \
    { return postprocess(joint->Getter()); }                                                            \
  else                                                                                                  \
    { return properties; }                                                                              \
} while(false)

/* ---------------------------------- PhysicsJoint -------------------------- */

PhysicsJoint::PhysicsJoint(Type type, PhysicsBody& first_physics_body, PhysicsBody& second_physics_body) :
  m_type(type),
  m_physics_world(nullptr),
  m_first_physics_body(first_physics_body),
  m_second_physics_body(second_physics_body),
  m_b2_joint(nullptr)
{

}

PhysicsJoint::~PhysicsJoint()
{
  destroyInternalJoint();
}

void PhysicsJoint::createInternalJoint()
{
  if(m_physics_world && !m_b2_joint)
  {
    auto b2_joint_def = createInternalJointDef(m_first_physics_body.getInternalBody(),
                                               m_second_physics_body.getInternalBody());
    b2_joint_def->userData.pointer = reinterpret_cast<uintptr_t>(this);

    m_b2_joint = m_physics_world->createInternalJoint(b2_joint_def.get());

    m_physics_world->attachPhysicsJoint(this);
    m_first_physics_body.attachPhysicsJoint(this);
    m_second_physics_body.attachPhysicsJoint(this);
  }
}

void PhysicsJoint::destroyInternalJoint()
{
  if (m_physics_world && m_b2_joint)
  {
    m_physics_world->destroyInternalJoint(m_b2_joint);

    m_physics_world->detachPhysicsJoint(this);
    m_first_physics_body.detachPhysicsJoint(this);
    m_second_physics_body.detachPhysicsJoint(this);
    m_b2_joint = nullptr;
  }
}

const PhysicsBody& PhysicsJoint::getFirstPhysicsBody() const
{
  return m_first_physics_body;
}

PhysicsBody& PhysicsJoint::getFirstPhysicsBody()
{
  return m_first_physics_body;
}

const PhysicsBody& PhysicsJoint::getSecondPhysicsBody() const
{
  return m_second_physics_body;
}

PhysicsBody& PhysicsJoint::getSecondPhysicsBody()
{
  return m_second_physics_body;
}

PhysicsJoint::Type PhysicsJoint::getType() const
{
  return m_type;
}

void PhysicsJoint::accept(scene::SceneVisitor& visitor)
{
  visitor.visitPhysicsJoint(*this);
}

void PhysicsJoint::onEnter()
{
  auto scene_node = getScene();
  m_physics_world = scene_node ? std::addressof(scene_node->getPhysicsWorld()) : nullptr;

  createInternalJoint();
  Node::onEnter();
}

void PhysicsJoint::onExit()
{
  destroyInternalJoint();

  auto scene_node = getScene();
  m_physics_world = scene_node ? std::addressof(scene_node->getPhysicsWorld()) : nullptr;

  Node::onExit();
}

/* ------------------------------ DistancePhysicsJoint ---------------------- */

std::unique_ptr<DistancePhysicsJoint> DistancePhysicsJoint::create(
  PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
  const sf::Vector2f& first_anchor, const sf::Vector2f& second_anchor)
{
  return std::unique_ptr<DistancePhysicsJoint>(new (std::nothrow) DistancePhysicsJoint(
    first_physics_body, second_physics_body, first_anchor, second_anchor));
}

DistancePhysicsJoint::DistancePhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                           const sf::Vector2f& first_anchor, const sf::Vector2f& second_anchor) :
  PhysicsJoint(Type::Distance, first_physics_body, second_physics_body),
  m_length(b2Max(math::VectorHelper::distance(first_anchor, second_anchor), b2_linearSlop)),
  m_min_length(m_length),
  m_max_length(m_length),
  m_stiffness(0.0f),
  m_damping(0.0f)
{
  m_first_local_anchor = getFirstPhysicsBody().getWorldTransform().getInverse().transformPoint(first_anchor);
  m_second_local_anchor = getSecondPhysicsBody().getWorldTransform().getInverse().transformPoint(second_anchor);
}

DistancePhysicsJoint::~DistancePhysicsJoint() = default;

void DistancePhysicsJoint::setLength(float length)
{
  PushPostProcessProperties(b2DistanceJoint, SetLength, length, priv::PhysicsHelper::pixel_to_meter(length), m_length);
}

float DistancePhysicsJoint::getLength() const
{
  PullPostProcessProperties(b2DistanceJoint, GetLength, m_length, priv::PhysicsHelper::meter_to_pixel);
}

void DistancePhysicsJoint::setMinLength(float min_length)
{
  PushPostProcessProperties(b2DistanceJoint, SetMinLength, min_length, priv::PhysicsHelper::pixel_to_meter(min_length), m_min_length);
}

float DistancePhysicsJoint::getMinLength() const
{
  PullPostProcessProperties(b2DistanceJoint, GetMinLength, m_min_length, priv::PhysicsHelper::meter_to_pixel);
}

void DistancePhysicsJoint::setMaxLength(float max_length)
{
  PushPostProcessProperties(b2DistanceJoint, SetMaxLength, max_length, priv::PhysicsHelper::pixel_to_meter(max_length), m_max_length);
}

float DistancePhysicsJoint::getMaxLength() const
{
  PullPostProcessProperties(b2DistanceJoint, GetMaxLength, m_max_length, priv::PhysicsHelper::meter_to_pixel);
}

float DistancePhysicsJoint::getCurrentLength() const
{
  PullPostProcessProperties(b2DistanceJoint, GetCurrentLength, m_length, priv::PhysicsHelper::meter_to_pixel);
}

void DistancePhysicsJoint::setStiffness(float stiffness)
{
  PushProperties(b2DistanceJoint, SetStiffness, stiffness, m_stiffness);
}

float DistancePhysicsJoint::getStiffness() const
{
  PullProperties(b2DistanceJoint, GetStiffness, m_stiffness);
}

void DistancePhysicsJoint::setDamping(float damping)
{
  PushProperties(b2DistanceJoint, SetDamping, damping, m_damping);
}

float DistancePhysicsJoint::getDamping() const
{
  PullProperties(b2DistanceJoint, GetDamping, m_damping);
}

sf::Vector2f DistancePhysicsJoint::getLocalFirstAnchor() const
{
  PullPostProcessProperties(b2DistanceJoint, GetLocalAnchorA, m_first_local_anchor, priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f DistancePhysicsJoint::getLocalSecondAnchor() const
{
  PullPostProcessProperties(b2DistanceJoint, GetLocalAnchorB, m_second_local_anchor, priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f DistancePhysicsJoint::getFirstAnchor() const
{
  auto world_point = getFirstPhysicsBody().getWorldTransform().transformPoint(m_first_local_anchor);
  PullPostProcessProperties(b2DistanceJoint, GetAnchorA, world_point, priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f DistancePhysicsJoint::getSecondAnchor() const
{
  auto world_point = getSecondPhysicsBody().getWorldTransform().transformPoint(m_second_local_anchor);
  PullPostProcessProperties(b2DistanceJoint, GetAnchorB, world_point, priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f DistancePhysicsJoint::getReactionForce(float inv_dt) const
{
  if(auto joint = getInternalJoint<b2DistanceJoint>(); joint) return priv::PhysicsHelper::cast(joint->GetReactionForce(inv_dt));
  else                                                        return sf::Vector2f();
}

float DistancePhysicsJoint::getReactionTorque(float inv_dt) const
{
  if(auto joint = getInternalJoint<b2DistanceJoint>(); joint) return joint->GetReactionTorque(inv_dt);
  else                                                        return 0.f;
}

std::unique_ptr<b2JointDef> DistancePhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_distance_joint_def = std::make_unique<b2DistanceJointDef>();

  b2_distance_joint_def->bodyA = b2_first_physics_body;
  b2_distance_joint_def->bodyB = b2_second_physics_body;
  b2_distance_joint_def->localAnchorA = priv::PhysicsHelper::pixel_to_meter(m_first_local_anchor);
  b2_distance_joint_def->localAnchorB = priv::PhysicsHelper::pixel_to_meter(m_second_local_anchor);
  b2_distance_joint_def->stiffness = m_stiffness;
  b2_distance_joint_def->damping = m_damping;
  b2_distance_joint_def->length = priv::PhysicsHelper::pixel_to_meter(m_length);
  b2_distance_joint_def->minLength = priv::PhysicsHelper::pixel_to_meter(m_min_length);
  b2_distance_joint_def->maxLength = priv::PhysicsHelper::pixel_to_meter(m_max_length);

  return b2_distance_joint_def;
}

/* ------------------------------ FrictionPhysicsJoint ---------------------- */

std::unique_ptr<FrictionPhysicsJoint> FrictionPhysicsJoint::create(
  PhysicsBody& first_physics_body, PhysicsBody& second_physics_body, const sf::Vector2f& anchor)
{
  return std::unique_ptr<FrictionPhysicsJoint>(new (std::nothrow) FrictionPhysicsJoint(
    first_physics_body, second_physics_body, anchor));
}

FrictionPhysicsJoint::FrictionPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                           const sf::Vector2f& anchor) :
  PhysicsJoint(Type::Friction, first_physics_body, second_physics_body),
  m_max_force(0),
  m_max_torque(0)
{
  m_first_local_anchor = getFirstPhysicsBody().getWorldTransform().getInverse().transformPoint(anchor);
  m_second_local_anchor = getSecondPhysicsBody().getWorldTransform().getInverse().transformPoint(anchor);
}

FrictionPhysicsJoint::~FrictionPhysicsJoint() = default;

void FrictionPhysicsJoint::setMaxForce(float force)
{
  PushProperties(b2FrictionJoint, SetMaxForce, force, m_max_force);
}

float FrictionPhysicsJoint::getMaxForce() const
{
  PullProperties(b2FrictionJoint, GetMaxForce, m_max_force);
}

void FrictionPhysicsJoint::setMaxTorque(float torque)
{
  PushProperties(b2FrictionJoint, SetMaxTorque, torque, m_max_torque);
}

float FrictionPhysicsJoint::getMaxTorque() const
{
  PullProperties(b2FrictionJoint, GetMaxForce, m_max_torque);
}

sf::Vector2f FrictionPhysicsJoint::getLocalFirstAnchor() const
{
  PullPostProcessProperties(b2FrictionJoint, GetLocalAnchorA, m_first_local_anchor, priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f FrictionPhysicsJoint::getLocalSecondAnchor() const
{
  PullPostProcessProperties(b2FrictionJoint, GetLocalAnchorB, m_second_local_anchor, priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f FrictionPhysicsJoint::getFirstAnchor() const
{
  auto world_point = getFirstPhysicsBody().getWorldTransform().transformPoint(m_first_local_anchor);
  PullPostProcessProperties(b2FrictionJoint, GetAnchorA, world_point, priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f FrictionPhysicsJoint::getSecondAnchor() const
{
  auto world_point = getSecondPhysicsBody().getWorldTransform().transformPoint(m_second_local_anchor);
  PullPostProcessProperties(b2FrictionJoint, GetAnchorB, world_point, priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f FrictionPhysicsJoint::getReactionForce(float inv_dt) const
{
  if(auto joint = getInternalJoint<b2FrictionJoint>(); joint) return priv::PhysicsHelper::cast(joint->GetReactionForce(inv_dt));
  else                                                        return sf::Vector2f();
}

float FrictionPhysicsJoint::getReactionTorque(float inv_dt) const
{
  if(auto joint = getInternalJoint<b2FrictionJoint>(); joint) return joint->GetReactionTorque(inv_dt);
  else                                                        return 0.f;
}

std::unique_ptr<b2JointDef> FrictionPhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_friction_joint_def = std::make_unique<b2FrictionJointDef>();

  b2_friction_joint_def->bodyA = b2_first_physics_body;
  b2_friction_joint_def->bodyB = b2_second_physics_body;
  b2_friction_joint_def->localAnchorA = priv::PhysicsHelper::pixel_to_meter(m_first_local_anchor);
  b2_friction_joint_def->localAnchorB = priv::PhysicsHelper::pixel_to_meter(m_second_local_anchor);
  b2_friction_joint_def->maxForce = m_max_force;
  b2_friction_joint_def->maxTorque = m_max_torque;

  return b2_friction_joint_def;
}

/* -------------------------------- MotorPhysicsJoint ----------------------- */

std::unique_ptr<MotorPhysicsJoint> MotorPhysicsJoint::create(
  PhysicsBody& first_physics_body, PhysicsBody& second_physics_body)
{
  return std::unique_ptr<MotorPhysicsJoint>(new (std::nothrow) MotorPhysicsJoint(
    first_physics_body, second_physics_body));
}

MotorPhysicsJoint::MotorPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body) :
  PhysicsJoint(Type::Motor, first_physics_body, second_physics_body),
  m_max_force(1.f),
  m_max_torque(1.f),
  m_correction_factory(0.3f)
{
  m_linear_offset = getFirstPhysicsBody().getWorldTransform().getInverse().transformPoint(getSecondPhysicsBody().getWorldPosition());
  m_angular_offset = getSecondPhysicsBody().getRotation() - getFirstPhysicsBody().getRotation();
}

MotorPhysicsJoint::~MotorPhysicsJoint() = default;

void MotorPhysicsJoint::setMaxForce(float force)
{
  PushProperties(b2MotorJoint, SetMaxForce, force, m_max_force);
}

float MotorPhysicsJoint::getMaxForce() const
{
  PullProperties(b2MotorJoint, GetMaxForce, m_max_force);
}

void MotorPhysicsJoint::setMaxTorque(float torque)
{
  PushProperties(b2MotorJoint, SetMaxTorque, torque, m_max_torque);
}

float MotorPhysicsJoint::getMaxTorque() const
{
  PullProperties(b2MotorJoint, GetMaxTorque, m_max_torque);
}

void MotorPhysicsJoint::setCorrectionFactory(float factory)
{
  PushProperties(b2MotorJoint, SetCorrectionFactor, factory, m_correction_factory);
}

float MotorPhysicsJoint::getCorrectionFactory() const
{
  PullProperties(b2MotorJoint, GetCorrectionFactor, m_correction_factory);
}

void MotorPhysicsJoint::setLinearOffset(const sf::Vector2f& linear_offset)
{
  PushPostProcessProperties(b2MotorJoint, SetLinearOffset, linear_offset,
                            priv::PhysicsHelper::pixel_to_meter(linear_offset), m_linear_offset);
}

sf::Vector2f MotorPhysicsJoint::getLinearOffset() const
{
  PullPostProcessProperties(b2MotorJoint, GetLinearOffset, m_linear_offset, priv::PhysicsHelper::meter_to_pixel);
}

void MotorPhysicsJoint::setAngularOffset(float angular_offset)
{
  PushProperties(b2MotorJoint, SetAngularOffset, angular_offset, m_angular_offset);
}

float MotorPhysicsJoint::getAngularOffset() const
{
  PullProperties(b2MotorJoint, GetAngularOffset, m_angular_offset);
}

sf::Vector2f MotorPhysicsJoint::getFirstAnchor() const
{
  return getFirstPhysicsBody().getPosition();
}

sf::Vector2f MotorPhysicsJoint::getSecondAnchor() const
{
  return getSecondPhysicsBody().getPosition();
}

sf::Vector2f MotorPhysicsJoint::getReactionForce(float inv_dt) const
{
  if(auto joint = getInternalJoint<b2MotorJoint>(); joint) return priv::PhysicsHelper::cast(joint->GetReactionForce(inv_dt));
  else                                                     return sf::Vector2f();
}

float MotorPhysicsJoint::getReactionTorque(float inv_dt) const
{
  if(auto joint = getInternalJoint<b2MotorJoint>(); joint) return joint->GetReactionTorque(inv_dt);
  else                                                     return 0.f;
}

std::unique_ptr<b2JointDef> MotorPhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_motor_joint_def = std::make_unique<b2MotorJointDef>();

  b2_motor_joint_def->bodyA = b2_first_physics_body;
  b2_motor_joint_def->bodyB = b2_second_physics_body;
  b2_motor_joint_def->maxForce = m_max_force;
  b2_motor_joint_def->maxTorque = m_max_torque;
  b2_motor_joint_def->correctionFactor = m_correction_factory;
  b2_motor_joint_def->angularOffset = priv::PhysicsHelper::angleToRadian(m_angular_offset);
  b2_motor_joint_def->linearOffset = priv::PhysicsHelper::pixel_to_meter(m_linear_offset);

  return b2_motor_joint_def;
}

/* ------------------------------ PrismaticPhysicsJoint --------------------- */

std::unique_ptr<PrismaticPhysicsJoint> PrismaticPhysicsJoint::create(
  PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
  const sf::Vector2f& anchor, const sf::Vector2f& axis)
{
  return std::unique_ptr<PrismaticPhysicsJoint>(new (std::nothrow) PrismaticPhysicsJoint(
    first_physics_body, second_physics_body, anchor, axis));
}

PrismaticPhysicsJoint::PrismaticPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                             const sf::Vector2f& anchor, const sf::Vector2f& axis) :
  PhysicsJoint(Type::Prismatic, first_physics_body, second_physics_body),
  m_enable_limit(false),
  m_max_motor_force(0.f),
  m_lower_translation(0.f),
  m_upper_translation(0.f),
  m_enable_motor(false),
  m_motor_speed(0.f)
{
  m_first_local_anchor = getFirstPhysicsBody().getWorldTransform().getInverse().transformPoint(anchor);
  m_second_local_anchor = getSecondPhysicsBody().getWorldTransform().getInverse().transformPoint(anchor);
  m_first_local_axis = getFirstPhysicsBody().getWorldTransform().getInverse().transformPoint(axis);
  m_reference_angle = getSecondPhysicsBody().getRotation() - getFirstPhysicsBody().getRotation();
}

PrismaticPhysicsJoint::~PrismaticPhysicsJoint() = default;

float PrismaticPhysicsJoint::getReferenceAngle() const
{
  PullPostProcessProperties(b2PrismaticJoint, GetReferenceAngle, m_reference_angle, priv::PhysicsHelper::radianToAngle);
}

float PrismaticPhysicsJoint::getJointTranslation() const
{
  auto pA = getFirstPhysicsBody().getWorldTransform().transformPoint(m_first_local_anchor);
  auto pB = getSecondPhysicsBody().getWorldTransform().transformPoint(m_second_local_anchor);
  auto axis = getFirstPhysicsBody().getWorldTransform().transformPoint(m_first_local_axis);

  auto d = pB - pA;
  auto translation = math::VectorHelper::dot(d, axis);
  return translation;
}

float PrismaticPhysicsJoint::getJointSpeed() const
{
  PullProperties(b2PrismaticJoint, GetJointSpeed, 0.f);
}

bool PrismaticPhysicsJoint::isLimitEnabled() const
{
  PullProperties(b2PrismaticJoint, IsLimitEnabled, m_enable_limit);
}

void PrismaticPhysicsJoint::enableLimit(bool enable)
{
  PushProperties(b2PrismaticJoint, EnableLimit, enable, m_enable_limit);
}

float PrismaticPhysicsJoint::getLowerLimit() const
{
  PullPostProcessProperties(b2PrismaticJoint, GetLowerLimit, m_lower_translation, priv::PhysicsHelper::meter_to_pixel);
}

float PrismaticPhysicsJoint::getUpperLimit() const
{
  PullPostProcessProperties(b2PrismaticJoint, GetUpperLimit, m_upper_translation, priv::PhysicsHelper::meter_to_pixel);
}

void PrismaticPhysicsJoint::setLimits(float lower, float upper)
{
  if(auto joint = getInternalJoint<b2PrismaticJoint>(); joint)
    joint->SetLimits(priv::PhysicsHelper::pixel_to_meter(lower),
                     priv::PhysicsHelper::pixel_to_meter(upper));
  else
  {
    m_lower_translation = lower;
    m_upper_translation = upper;
  }
}

bool PrismaticPhysicsJoint::isMotorEnabled() const
{
  PullProperties(b2PrismaticJoint, IsMotorEnabled, m_enable_motor);
}

void PrismaticPhysicsJoint::enableMotor(bool enable)
{
  PushProperties(b2PrismaticJoint, EnableMotor, enable, m_enable_motor);
}

void PrismaticPhysicsJoint::setMotorSpeed(float speed)
{
  PushProperties(b2PrismaticJoint, SetMotorSpeed, speed, m_motor_speed);
}

float PrismaticPhysicsJoint::getMotorSpeed() const
{
  PullProperties(b2PrismaticJoint, GetMotorSpeed, m_motor_speed);
}

void PrismaticPhysicsJoint::setMaxMotorForce(float force)
{
  PushProperties(b2PrismaticJoint, SetMaxMotorForce, force, m_max_motor_force);
}

float PrismaticPhysicsJoint::getMaxMotorForce() const
{
  PullProperties(b2PrismaticJoint, GetMaxMotorForce, m_max_motor_force);
}

float PrismaticPhysicsJoint::getMotorForce(float inv_dt) const
{
  if(auto joint = getInternalJoint<b2PrismaticJoint>(); joint) return joint->GetMotorForce(inv_dt);
  else                                                         return 0.f;
}

sf::Vector2f PrismaticPhysicsJoint::getFirstAnchor() const
{
  auto world_point = getFirstPhysicsBody().getWorldTransform().transformPoint(m_first_local_anchor);
  PullPostProcessProperties(b2PrismaticJoint, GetAnchorA, world_point, priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f PrismaticPhysicsJoint::getSecondAnchor() const
{
  auto world_point = getSecondPhysicsBody().getWorldTransform().transformPoint(m_second_local_anchor);
  PullPostProcessProperties(b2PrismaticJoint, GetAnchorA, world_point, priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f PrismaticPhysicsJoint::getReactionForce(float inv_dt) const
{
  if(auto joint = getInternalJoint<b2PrismaticJoint>(); joint) return priv::PhysicsHelper::cast(joint->GetReactionForce(inv_dt));
  else                                                         return sf::Vector2f();
}

float PrismaticPhysicsJoint::getReactionTorque(float inv_dt) const
{
  if(auto joint = getInternalJoint<b2PrismaticJoint>(); joint) return joint->GetReactionTorque(inv_dt);
  else                                                         return 0.f;
}

std::unique_ptr<b2JointDef> PrismaticPhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_prismatic_joint_def = std::make_unique<b2PrismaticJointDef>();

  b2_prismatic_joint_def->bodyA = b2_first_physics_body;
  b2_prismatic_joint_def->bodyB = b2_second_physics_body;
  b2_prismatic_joint_def->localAnchorA = priv::PhysicsHelper::pixel_to_meter(m_first_local_anchor);
  b2_prismatic_joint_def->localAnchorB = priv::PhysicsHelper::pixel_to_meter(m_second_local_anchor);
  b2_prismatic_joint_def->localAxisA = priv::PhysicsHelper::pixel_to_meter(m_first_local_axis);
  b2_prismatic_joint_def->enableLimit = m_enable_limit;
  b2_prismatic_joint_def->enableMotor = m_enable_motor;
  b2_prismatic_joint_def->motorSpeed = m_motor_speed;
  b2_prismatic_joint_def->maxMotorForce = m_max_motor_force;
  b2_prismatic_joint_def->referenceAngle = priv::PhysicsHelper::angleToRadian(m_reference_angle);
  b2_prismatic_joint_def->lowerTranslation = priv::PhysicsHelper::pixel_to_meter(m_lower_translation);
  b2_prismatic_joint_def->upperTranslation = priv::PhysicsHelper::pixel_to_meter(m_upper_translation);

  return b2_prismatic_joint_def;
}

/* ------------------------------- PulleyPhysicsJoint ----------------------- */

std::unique_ptr<PulleyPhysicsJoint> PulleyPhysicsJoint::create(
  PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
  const sf::Vector2f& first_ground_anchor, const sf::Vector2f& second_ground_anchor,
  const sf::Vector2f& first_anchor, const sf::Vector2f& second_anchor, float ratio)
{
  return std::unique_ptr<PulleyPhysicsJoint>(new (std::nothrow) PulleyPhysicsJoint(
    first_physics_body, second_physics_body, first_ground_anchor, second_ground_anchor,
    first_anchor, second_anchor, ratio));
}

PulleyPhysicsJoint::PulleyPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                       const sf::Vector2f& first_ground_anchor, const sf::Vector2f& second_ground_anchor,
                                       const sf::Vector2f& first_anchor, const sf::Vector2f& second_anchor, float ratio) :
  PhysicsJoint(Type::Pulley, first_physics_body, second_physics_body),
  m_first_ground_anchor(first_ground_anchor),
  m_second_ground_anchor(second_ground_anchor),
  m_ratio(ratio)
{
  m_first_local_anchor = getFirstPhysicsBody().getWorldTransform().getInverse().transformPoint(first_anchor);
  m_second_local_anchor = getSecondPhysicsBody().getWorldTransform().getInverse().transformPoint(second_anchor);
  m_first_length = math::VectorHelper::distance(first_anchor, first_ground_anchor);
  m_second_length = math::VectorHelper::distance(second_anchor, second_ground_anchor);
}

PulleyPhysicsJoint::~PulleyPhysicsJoint() = default;

float PulleyPhysicsJoint::getFirstLength() const
{
  PullProperties(b2PulleyJoint, GetLengthA, m_first_length);
}

float PulleyPhysicsJoint::getSecondLength() const
{
  PullProperties(b2PulleyJoint, GetLengthB, m_second_length);
}

float PulleyPhysicsJoint::getRation() const
{
  PullProperties(b2PulleyJoint, GetRatio, m_ratio);
}

sf::Vector2f PulleyPhysicsJoint::getFirstGroundAnchor() const
{
  PullPostProcessProperties(b2PulleyJoint, GetGroundAnchorA, m_first_ground_anchor,priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f PulleyPhysicsJoint::getSecondGroundAnchor() const
{
  PullPostProcessProperties(b2PulleyJoint, GetGroundAnchorB, m_second_ground_anchor,priv::PhysicsHelper::meter_to_pixel);
}

float PulleyPhysicsJoint::getCurrentFirstLength() const
{
  auto p = getFirstPhysicsBody().getWorldTransform().transformPoint(m_first_local_anchor);
  auto s = m_first_ground_anchor;
  return math::VectorHelper::distance(p, s);
}

float PulleyPhysicsJoint::getCurrentSecondLength() const
{
  auto p = getFirstPhysicsBody().getWorldTransform().transformPoint(m_second_local_anchor);
  auto s = m_second_ground_anchor;
  return math::VectorHelper::distance(p, s);
}

sf::Vector2f PulleyPhysicsJoint::getFirstAnchor() const
{
  auto world_point = getFirstPhysicsBody().getWorldTransform().transformPoint(m_first_local_anchor);
  PullPostProcessProperties(b2PulleyJoint, GetAnchorA, world_point, priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f PulleyPhysicsJoint::getSecondAnchor() const
{
  auto world_point = getSecondPhysicsBody().getWorldTransform().transformPoint(m_second_local_anchor);
  PullPostProcessProperties(b2PulleyJoint, GetAnchorB, world_point, priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f PulleyPhysicsJoint::getReactionForce(float inv_dt) const
{
  if(auto joint = getInternalJoint<b2PulleyJoint>(); joint) return priv::PhysicsHelper::cast(joint->GetReactionForce(inv_dt));
  else                                                      return sf::Vector2f();
}

float PulleyPhysicsJoint::getReactionTorque(float inv_dt) const
{
  if(auto joint = getInternalJoint<b2PulleyJoint>(); joint) return joint->GetReactionTorque(inv_dt);
  else                                                      return 0.f;
}

std::unique_ptr<b2JointDef> PulleyPhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_pulley_joint_def = std::make_unique<b2PulleyJointDef>();

  b2_pulley_joint_def->bodyA = b2_first_physics_body;
  b2_pulley_joint_def->bodyB = b2_second_physics_body;
  b2_pulley_joint_def->localAnchorA = priv::PhysicsHelper::pixel_to_meter(m_first_local_anchor);
  b2_pulley_joint_def->localAnchorB = priv::PhysicsHelper::pixel_to_meter(m_second_local_anchor);
  b2_pulley_joint_def->groundAnchorA = priv::PhysicsHelper::pixel_to_meter(m_first_ground_anchor);
  b2_pulley_joint_def->groundAnchorB = priv::PhysicsHelper::pixel_to_meter(m_second_ground_anchor);
  b2_pulley_joint_def->lengthA = m_first_length;
  b2_pulley_joint_def->lengthB = m_second_length;
  b2_pulley_joint_def->ratio = m_ratio;

  return b2_pulley_joint_def;
}

/* ------------------------------ RevolutePhysicsJoint ---------------------- */

std::unique_ptr<RevolutePhysicsJoint> RevolutePhysicsJoint::create(
  PhysicsBody& first_physics_body, PhysicsBody& second_physics_body, const sf::Vector2f& anchor)
{
  return std::unique_ptr<RevolutePhysicsJoint>(new (std::nothrow) RevolutePhysicsJoint(
    first_physics_body, second_physics_body, anchor));
}

RevolutePhysicsJoint::RevolutePhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                           const sf::Vector2f& anchor) :
  PhysicsJoint(Type::Revolute, first_physics_body, second_physics_body),
  m_enable_limit(false),
  m_max_motor_torque(0.f),
  m_lower_angle(0.f),
  m_upper_angle(0.f),
  m_enable_motor(false),
  m_motor_speed(0.f)
{
  m_first_local_anchor = getFirstPhysicsBody().getWorldTransform().getInverse().transformPoint(anchor);
  m_second_local_anchor = getSecondPhysicsBody().getWorldTransform().getInverse().transformPoint(anchor);
  m_reference_angle = getSecondPhysicsBody().getRotation() - getFirstPhysicsBody().getRotation();
}

RevolutePhysicsJoint::~RevolutePhysicsJoint() = default;

float RevolutePhysicsJoint::getReferenceAngle() const
{
  PullPostProcessProperties(b2RevoluteJoint, GetReferenceAngle, m_reference_angle, priv::PhysicsHelper::radianToAngle);
}

float RevolutePhysicsJoint::getJointAngle() const
{
  PullPostProcessProperties(b2RevoluteJoint, GetJointAngle, 0.f, priv::PhysicsHelper::radianToAngle);
}

float RevolutePhysicsJoint::getJointSpeed() const
{
  PullProperties(b2RevoluteJoint, GetJointSpeed, 0.f);
}

bool RevolutePhysicsJoint::isLimitEnabled() const
{
  PullProperties(b2RevoluteJoint, IsLimitEnabled, m_enable_limit);
}

void RevolutePhysicsJoint::enableLimit(bool enable)
{
  PushProperties(b2RevoluteJoint, EnableLimit, enable, m_enable_limit);
}

float RevolutePhysicsJoint::getLowerLimit() const
{
  PullPostProcessProperties(b2RevoluteJoint, GetLowerLimit, m_lower_angle, priv::PhysicsHelper::radianToAngle);
}

float RevolutePhysicsJoint::getUpperLimit() const
{
  PullPostProcessProperties(b2RevoluteJoint, GetUpperLimit, m_upper_angle, priv::PhysicsHelper::radianToAngle);
}

void RevolutePhysicsJoint::setLimits(float lower, float upper)
{
  if(auto joint = getInternalJoint<b2RevoluteJoint>(); joint)
    joint->SetLimits(priv::PhysicsHelper::angleToRadian(lower),
                     priv::PhysicsHelper::angleToRadian(upper));
  else
  {
    m_lower_angle = lower;
    m_upper_angle = upper;
  }
}

bool RevolutePhysicsJoint::isMotorEnabled() const
{
  PullProperties(b2RevoluteJoint, IsMotorEnabled, m_enable_motor);
}

void RevolutePhysicsJoint::enableMotor(bool enable)
{
  PushProperties(b2RevoluteJoint, EnableMotor, enable, m_enable_motor);
}

void RevolutePhysicsJoint::setMotorSpeed(float speed)
{
  PushProperties(b2RevoluteJoint, SetMotorSpeed, speed, m_motor_speed);
}

float RevolutePhysicsJoint::getMotorSpeed() const
{
  PullProperties(b2RevoluteJoint, GetMotorSpeed, m_motor_speed);
}

void RevolutePhysicsJoint::setMaxMotorTorque(float torque)
{
  PushProperties(b2RevoluteJoint, SetMaxMotorTorque, torque, m_max_motor_torque);
}

float RevolutePhysicsJoint::getMaxMotorTorque() const
{
  PullProperties(b2RevoluteJoint, GetMaxMotorTorque, m_max_motor_torque);
}

float RevolutePhysicsJoint::getMotorTorque(float inv_dt) const
{
  if(auto joint = getInternalJoint<b2RevoluteJoint>(); joint) return joint->GetMotorTorque(inv_dt);
  else                                                        return 0.f;
}

sf::Vector2f RevolutePhysicsJoint::getFirstAnchor() const
{
  auto world_point = getFirstPhysicsBody().getWorldTransform().transformPoint(m_first_local_anchor);
  PullPostProcessProperties(b2RevoluteJoint, GetAnchorA, world_point, priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f RevolutePhysicsJoint::getSecondAnchor() const
{
  auto world_point = getSecondPhysicsBody().getWorldTransform().transformPoint(m_second_local_anchor);
  PullPostProcessProperties(b2RevoluteJoint, GetAnchorB, world_point, priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f RevolutePhysicsJoint::getReactionForce(float inv_dt) const
{
  if(auto joint = getInternalJoint<b2RevoluteJoint>(); joint) return priv::PhysicsHelper::cast(joint->GetReactionForce(inv_dt));
  else                                                        return sf::Vector2f();
}

float RevolutePhysicsJoint::getReactionTorque(float inv_dt) const
{
  if(auto joint = getInternalJoint<b2RevoluteJoint>(); joint) return joint->GetReactionTorque(inv_dt);
  else                                                        return 0.f;
}

std::unique_ptr<b2JointDef> RevolutePhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_revolute_joint_def = std::make_unique<b2RevoluteJointDef>();

  b2_revolute_joint_def->bodyA = b2_first_physics_body;
  b2_revolute_joint_def->bodyB = b2_second_physics_body;
  b2_revolute_joint_def->localAnchorA = priv::PhysicsHelper::pixel_to_meter(m_first_local_anchor);
  b2_revolute_joint_def->localAnchorB = priv::PhysicsHelper::pixel_to_meter(m_second_local_anchor);
  b2_revolute_joint_def->enableLimit = m_enable_limit;
  b2_revolute_joint_def->enableMotor = m_enable_motor;
  b2_revolute_joint_def->motorSpeed = m_motor_speed;
  b2_revolute_joint_def->maxMotorTorque = m_max_motor_torque;
  b2_revolute_joint_def->referenceAngle = priv::PhysicsHelper::angleToRadian(m_reference_angle);
  b2_revolute_joint_def->lowerAngle = priv::PhysicsHelper::angleToRadian(m_lower_angle);
  b2_revolute_joint_def->upperAngle = priv::PhysicsHelper::angleToRadian(m_upper_angle);

  return b2_revolute_joint_def;
}

/* -------------------------------- WeldPhysicsJoint ------------------------ */

std::unique_ptr<WeldPhysicsJoint> WeldPhysicsJoint::create(
  PhysicsBody& first_physics_body, PhysicsBody& second_physics_body, const sf::Vector2f& anchor)
{
  return std::unique_ptr<WeldPhysicsJoint>(new (std::nothrow) WeldPhysicsJoint(
    first_physics_body, second_physics_body, anchor));
}

WeldPhysicsJoint::WeldPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                   const sf::Vector2f& anchor) :
  PhysicsJoint(Type::Weld, first_physics_body, second_physics_body),
  m_stiffness(0.f)
{
  m_first_local_anchor = getFirstPhysicsBody().getWorldTransform().getInverse().transformPoint(anchor);
  m_second_local_anchor = getSecondPhysicsBody().getWorldTransform().getInverse().transformPoint(anchor);
  m_reference_angle = getSecondPhysicsBody().getRotation() - getFirstPhysicsBody().getRotation();
}

WeldPhysicsJoint::~WeldPhysicsJoint() = default;

float WeldPhysicsJoint::getReferenceAngle() const
{
  PullPostProcessProperties(b2WeldJoint, GetReferenceAngle, m_reference_angle, priv::PhysicsHelper::radianToAngle);
}

void WeldPhysicsJoint::setStiffness(float stiffness)
{
  PushProperties(b2WeldJoint, SetStiffness, stiffness, m_stiffness);
}

float WeldPhysicsJoint::getStiffness() const
{
  PullProperties(b2WeldJoint, GetStiffness, m_stiffness);
}

sf::Vector2f WeldPhysicsJoint::getFirstAnchor() const
{
  auto world_point = getFirstPhysicsBody().getWorldTransform().transformPoint(m_first_local_anchor);
  PullPostProcessProperties(b2WeldJoint, GetAnchorA, world_point, priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f WeldPhysicsJoint::getSecondAnchor() const
{
  auto world_point = getSecondPhysicsBody().getWorldTransform().transformPoint(m_second_local_anchor);
  PullPostProcessProperties(b2WeldJoint, GetAnchorB, world_point, priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f WeldPhysicsJoint::getReactionForce(float inv_dt) const
{
  if(auto joint = getInternalJoint<b2WeldJoint>(); joint) return priv::PhysicsHelper::cast(joint->GetReactionForce(inv_dt));
  else                                                    return sf::Vector2f();
}

float WeldPhysicsJoint::getReactionTorque(float inv_dt) const
{
  if(auto joint = getInternalJoint<b2WeldJoint>(); joint) return joint->GetReactionTorque(inv_dt);
  else                                                    return 0.f;
}

std::unique_ptr<b2JointDef> WeldPhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_weld_joint_def = std::make_unique<b2WeldJointDef>();

  b2_weld_joint_def->bodyA = b2_first_physics_body;
  b2_weld_joint_def->bodyB = b2_second_physics_body;
  b2_weld_joint_def->localAnchorA = priv::PhysicsHelper::pixel_to_meter(m_first_local_anchor);
  b2_weld_joint_def->localAnchorB = priv::PhysicsHelper::pixel_to_meter(m_second_local_anchor);
  b2_weld_joint_def->referenceAngle = priv::PhysicsHelper::angleToRadian(m_reference_angle);
  b2_weld_joint_def->stiffness = m_stiffness;

  return b2_weld_joint_def;
}

/* ------------------------------- WheelPhysicsJoint ------------------------ */

std::unique_ptr<WheelPhysicsJoint> WheelPhysicsJoint::create(
  PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
  const sf::Vector2f& anchor, const sf::Vector2f& axis)
{
  return std::unique_ptr<WheelPhysicsJoint>(new (std::nothrow) WheelPhysicsJoint(
    first_physics_body, second_physics_body, anchor, axis));
}

WheelPhysicsJoint::WheelPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                     const sf::Vector2f& anchor, const sf::Vector2f& axis) :
  PhysicsJoint(Type::Wheel, first_physics_body, second_physics_body),
  m_enable_limit(false),
  m_enable_motor(false),
  m_lower_translation(0.f),
  m_upper_translation(0.f),
  m_motor_speed(0.f),
  m_max_motor_torque(0.f),
  m_stiffness(0.f),
  m_damping(0.f)
{
  m_first_local_anchor = getFirstPhysicsBody().getWorldTransform().getInverse().transformPoint(anchor);
  m_second_local_anchor = getSecondPhysicsBody().getWorldTransform().getInverse().transformPoint(anchor);
  m_first_local_axis = getFirstPhysicsBody().getWorldTransform().getInverse().transformPoint(axis);
}

WheelPhysicsJoint::~WheelPhysicsJoint() = default;

float WheelPhysicsJoint::getJointTranslation() const
{
  auto pA = getFirstPhysicsBody().getWorldTransform().transformPoint(m_first_local_anchor);
  auto pB = getSecondPhysicsBody().getWorldTransform().transformPoint(m_second_local_anchor);
  auto axis = getFirstPhysicsBody().getWorldTransform().transformPoint(m_first_local_axis);

  auto d = pB - pA;
  auto translation = math::VectorHelper::dot(d, axis);
  return translation;
}

float WheelPhysicsJoint::getJointLinearSpeed() const
{
  PullProperties(b2WheelJoint, GetJointLinearSpeed, 0.f);
}

float WheelPhysicsJoint::getJointAngle() const
{
  PullPostProcessProperties(b2WheelJoint, GetJointAngle, 0.f, priv::PhysicsHelper::radianToAngle);
}

float WheelPhysicsJoint::getJointAngularSpeed() const
{
  PullProperties(b2WheelJoint, GetJointAngularSpeed, 0.f);
}

bool WheelPhysicsJoint::isLimitEnabled() const
{
  PullProperties(b2WheelJoint, IsLimitEnabled, m_enable_limit);
}

void WheelPhysicsJoint::enableLimit(bool enable)
{
  PushProperties(b2WheelJoint, EnableLimit, enable, m_enable_limit);
}

float WheelPhysicsJoint::getLowerLimit() const
{
  PullPostProcessProperties(b2PrismaticJoint, GetLowerLimit, m_lower_translation, priv::PhysicsHelper::meter_to_pixel);
}

float WheelPhysicsJoint::getUpperLimit() const
{
  PullPostProcessProperties(b2PrismaticJoint, GetUpperLimit, m_upper_translation, priv::PhysicsHelper::meter_to_pixel);
}

void WheelPhysicsJoint::setLimits(float lower, float upper)
{
  if(auto joint = getInternalJoint<b2WheelJoint>(); joint)
    joint->SetLimits(priv::PhysicsHelper::pixel_to_meter(lower),
                     priv::PhysicsHelper::pixel_to_meter(upper));
  else
  {
    m_lower_translation = lower;
    m_upper_translation = upper;
  }
}

bool WheelPhysicsJoint::isMotorEnabled() const
{
  PullProperties(b2WheelJoint, IsMotorEnabled, m_enable_motor);
}

void WheelPhysicsJoint::enableMotor(bool enable)
{
  PushProperties(b2WheelJoint, EnableMotor, enable, m_enable_motor);
}

void WheelPhysicsJoint::setMotorSpeed(float speed)
{
  PushProperties(b2RevoluteJoint, SetMotorSpeed, speed, m_motor_speed);
}

float WheelPhysicsJoint::getMotorSpeed() const
{
  PullProperties(b2WheelJoint, GetMotorSpeed, m_motor_speed);
}

void WheelPhysicsJoint::setMaxMotorTorque(float torque)
{
  PushProperties(b2WheelJoint, SetMaxMotorTorque, torque, m_max_motor_torque);
}

float WheelPhysicsJoint::getMaxMotorTorque() const
{
  PullProperties(b2WheelJoint, GetMaxMotorTorque, m_max_motor_torque);
}

float WheelPhysicsJoint::getMotorTorque(float inv_dt)
{
  if(auto joint = getInternalJoint<b2WheelJoint>(); joint) return joint->GetMotorTorque(inv_dt);
  else                                                     return 0.f;
}

void WheelPhysicsJoint::setStiffness(float stiffness)
{
  PushProperties(b2WheelJoint, SetStiffness, stiffness, m_stiffness);
}

float WheelPhysicsJoint::getStiffness() const
{
  PullProperties(b2WheelJoint, GetStiffness, m_stiffness);
}

void WheelPhysicsJoint::setDamping(float damping)
{
  PushProperties(b2WheelJoint, SetDamping, damping, m_damping);
}

float WheelPhysicsJoint::getDamping() const
{
  PullProperties(b2WheelJoint, GetDamping, m_damping);
}

sf::Vector2f WheelPhysicsJoint::getFirstAnchor() const
{
  auto world_point = getFirstPhysicsBody().getWorldTransform().transformPoint(m_first_local_anchor);
  PullPostProcessProperties(b2WheelJoint, GetAnchorA, world_point, priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f WheelPhysicsJoint::getSecondAnchor() const
{
  auto world_point = getSecondPhysicsBody().getWorldTransform().transformPoint(m_second_local_anchor);
  PullPostProcessProperties(b2WheelJoint, GetAnchorB, world_point, priv::PhysicsHelper::meter_to_pixel);
}

sf::Vector2f WheelPhysicsJoint::getReactionForce(float inv_dt) const
{
  if(auto joint = getInternalJoint<b2WheelJoint>(); joint) return priv::PhysicsHelper::cast(joint->GetReactionForce(inv_dt));
  else                                                     return sf::Vector2f();
}

float WheelPhysicsJoint::getReactionTorque(float inv_dt) const
{
  if(auto joint = getInternalJoint<b2WheelJoint>(); joint) return joint->GetReactionTorque(inv_dt);
  else                                                     return 0.f;
}

std::unique_ptr<b2JointDef> WheelPhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_wheel_joint_def = std::make_unique<b2WheelJointDef>();

  b2_wheel_joint_def->bodyA = b2_first_physics_body;
  b2_wheel_joint_def->bodyB = b2_second_physics_body;
  b2_wheel_joint_def->localAnchorA = priv::PhysicsHelper::pixel_to_meter(m_first_local_anchor);
  b2_wheel_joint_def->localAnchorB = priv::PhysicsHelper::pixel_to_meter(m_second_local_anchor);
  b2_wheel_joint_def->localAxisA = priv::PhysicsHelper::pixel_to_meter(m_first_local_axis);
  b2_wheel_joint_def->enableLimit = m_enable_limit;
  b2_wheel_joint_def->enableMotor = m_enable_motor;
  b2_wheel_joint_def->motorSpeed = m_motor_speed;
  b2_wheel_joint_def->maxMotorTorque = m_max_motor_torque;
  b2_wheel_joint_def->lowerTranslation = priv::PhysicsHelper::pixel_to_meter(m_lower_translation);
  b2_wheel_joint_def->upperTranslation = priv::PhysicsHelper::pixel_to_meter(m_upper_translation);
  b2_wheel_joint_def->stiffness = m_stiffness;
  b2_wheel_joint_def->damping = m_damping;

  return b2_wheel_joint_def;
}

} // namespace egnim::physics