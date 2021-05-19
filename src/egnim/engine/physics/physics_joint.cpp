/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_joint.h>
#include <egnim/engine/physics/physics_body.h>
#include <egnim/engine/physics/physics_world.h>
#include <egnim/engine/physics/priv/physics_helper.h>
#include <egnim/engine/scene/scene_node.h>
#include <egnim/engine/math/vector_helper.h>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
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
  if(m_physics_world)
  {
    assert(!m_b2_joint);
    assert(m_physics_world);

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
  if (m_physics_world)
  {
    assert(m_b2_joint);
    assert(m_physics_world);

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

std::unique_ptr<scene::Node> PhysicsJoint::clone() const
{
  // TODO //
}

void PhysicsJoint::accept(scene::SceneVisitor& visitor)
{
  // TODO //
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
  b2_distance_joint_def->localAnchorA = priv::PhysicsHelper::pixel_to_meter(m_second_local_anchor);
  b2_distance_joint_def->stiffness = m_stiffness;
  b2_distance_joint_def->damping = m_damping;
  b2_distance_joint_def->length = m_length;
  b2_distance_joint_def->minLength = m_min_length;
  b2_distance_joint_def->maxLength = m_max_length;

  return b2_distance_joint_def;
}

/* ------------------------------ FrictionPhysicsJoint ---------------------- */

FrictionPhysicsJoint::FrictionPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                           const sf::Vector2f& anchor) :
  PhysicsJoint(Type::Friction, first_physics_body, second_physics_body),
  m_max_force(0),
  m_max_torque(0)
{
  m_first_local_anchor = getFirstPhysicsBody().getWorldTransform().getInverse().transformPoint(anchor);
  m_second_local_anchor = getSecondPhysicsBody().getWorldTransform().getInverse().transformPoint(anchor);
}

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
  b2_friction_joint_def->localAnchorA = priv::PhysicsHelper::pixel_to_meter(m_second_local_anchor);
  b2_friction_joint_def->maxForce = m_max_force;
  b2_friction_joint_def->maxTorque = m_max_torque;

  return b2_friction_joint_def;
}

/* -------------------------------- MotorPhysicsJoint ----------------------- */

MotorPhysicsJoint::MotorPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body) :
  PhysicsJoint(Type::Motor, first_physics_body, second_physics_body),
  m_max_force(1.f),
  m_max_torque(1.f),
  m_correction_factory(0.3f)
{
  m_linear_offset = getFirstPhysicsBody().getWorldTransform().getInverse().transformPoint(getSecondPhysicsBody().getWorldPosition());
  m_angular_offset = getSecondPhysicsBody().getRotation() - getFirstPhysicsBody().getRotation();
}

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

float PrismaticPhysicsJoint::getReferenceAngle() const
{
  PullProperties(b2PrismaticJoint, GetReferenceAngle, m_reference_angle);
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
  PullProperties(b2PrismaticJoint, GetLowerLimit, m_lower_translation);
}

float PrismaticPhysicsJoint::getUpperLimit() const
{
  PullProperties(b2PrismaticJoint, GetUpperLimit, m_upper_translation);
}

void PrismaticPhysicsJoint::setLimits(float lower, float upper)
{
  if(auto joint = getInternalJoint<b2PrismaticJoint>(); joint)
    joint->SetLimits(lower, upper);
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
  b2_prismatic_joint_def->localAnchorA = priv::PhysicsHelper::pixel_to_meter(m_second_local_anchor);
  b2_prismatic_joint_def->localAnchorA = priv::PhysicsHelper::pixel_to_meter(m_first_local_axis);
  b2_prismatic_joint_def->enableLimit = m_enable_limit;
  b2_prismatic_joint_def->enableMotor = m_enable_motor;
  b2_prismatic_joint_def->motorSpeed = m_motor_speed;
  b2_prismatic_joint_def->maxMotorForce = m_max_motor_force;
  b2_prismatic_joint_def->referenceAngle = priv::PhysicsHelper::angleToRadian(m_reference_angle);
  b2_prismatic_joint_def->lowerTranslation = m_lower_translation;
  b2_prismatic_joint_def->upperTranslation = m_upper_translation;

  return b2_prismatic_joint_def;
}

/* ------------------------------- PulleyPhysicsJoint ----------------------- */

PulleyPhysicsJoint::PulleyPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                       const sf::Vector2f& first_ground_anchor, const sf::Vector2f& second_ground_anchor,
                                       const sf::Vector2f& first_anchor, const sf::Vector2f& second_anchor, float ration) :
  PhysicsJoint(Type::Pulley, first_physics_body, second_physics_body),
  m_first_ground_anchor(first_ground_anchor),
  m_second_ground_anchor(second_ground_anchor),
  m_first_anchor(first_anchor),
  m_second_anchor(second_anchor),
  m_ration(ration)
{

}

sf::Vector2f PulleyPhysicsJoint::getFirstGroundAnchor() const
{
  auto first_ground_anchor = getInternalJoint<b2PulleyJoint>()->GetGroundAnchorA();
  return priv::PhysicsHelper::meter_to_pixel(first_ground_anchor);
}

sf::Vector2f PulleyPhysicsJoint::getSecondGroundAnchor() const
{
  auto second_ground_anchor = getInternalJoint<b2PulleyJoint>()->GetGroundAnchorB();
  return priv::PhysicsHelper::meter_to_pixel(second_ground_anchor);
}

float PulleyPhysicsJoint::getFirstLength() const
{
  return priv::PhysicsHelper::meter_to_pixel(getInternalJoint<b2PulleyJoint>()->GetLengthA());
}

float PulleyPhysicsJoint::getSecondLength() const
{
  return priv::PhysicsHelper::meter_to_pixel(getInternalJoint<b2PulleyJoint>()->GetLengthB());
}

float PulleyPhysicsJoint::getRation() const
{
  return getInternalJoint<b2PulleyJoint>()->GetRatio();
}

float PulleyPhysicsJoint::getCurrentFirstLength() const
{
  return priv::PhysicsHelper::meter_to_pixel(getInternalJoint<b2PulleyJoint>()->GetCurrentLengthA());
}

float PulleyPhysicsJoint::getCurrentSecondLength() const
{
  return priv::PhysicsHelper::meter_to_pixel(getInternalJoint<b2PulleyJoint>()->GetCurrentLengthB());
}

sf::Vector2f PulleyPhysicsJoint::getFirstAnchor() const
{
  // TODO //
}

sf::Vector2f PulleyPhysicsJoint::getSecondAnchor() const
{
  // TODO //
}

sf::Vector2f PulleyPhysicsJoint::getReactionForce(float inv_dt) const
{
  // TODO //
}

float PulleyPhysicsJoint::getReactionTorque(float inv_dt) const
{
  // TODO //
}

std::unique_ptr<b2JointDef> PulleyPhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_pulley_joint_def = std::make_unique<b2PulleyJointDef>();
  b2_pulley_joint_def->Initialize(b2_first_physics_body, b2_second_physics_body,
                                  priv::PhysicsHelper::pixel_to_meter(m_first_ground_anchor),
                                  priv::PhysicsHelper::pixel_to_meter(m_second_ground_anchor),
                                  priv::PhysicsHelper::pixel_to_meter(m_first_anchor),
                                  priv::PhysicsHelper::pixel_to_meter(m_second_anchor),
                                  m_ration);

  return b2_pulley_joint_def;
}

/* ------------------------------ RevolutePhysicsJoint ---------------------- */

RevolutePhysicsJoint::RevolutePhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                           const sf::Vector2f& anchor) :
  PhysicsJoint(Type::Revolute, first_physics_body, second_physics_body),
  m_anchor(anchor)
{

}

float RevolutePhysicsJoint::getReferenceAngle() const
{
  return getInternalJoint<b2RevoluteJoint>()->GetReferenceAngle();
}

float RevolutePhysicsJoint::getJointAngle() const
{
  return getInternalJoint<b2RevoluteJoint>()->GetJointAngle();
}

float RevolutePhysicsJoint::getJointSpeed() const
{
  return getInternalJoint<b2RevoluteJoint>()->GetJointSpeed();
}

bool RevolutePhysicsJoint::isLimitEnabled() const
{
  return getInternalJoint<b2RevoluteJoint>()->IsLimitEnabled();
}

void RevolutePhysicsJoint::enableLimit(bool enable)
{
  getInternalJoint<b2RevoluteJoint>()->EnableLimit(enable);
}

float RevolutePhysicsJoint::getLowerLimit() const
{
  return getInternalJoint<b2RevoluteJoint>()->GetLowerLimit();
}

float RevolutePhysicsJoint::getUppedLimit() const
{
  return getInternalJoint<b2RevoluteJoint>()->GetUpperLimit();
}

void RevolutePhysicsJoint::setLimits(float lower, float upper)
{
  getInternalJoint<b2RevoluteJoint>()->SetLimits(lower, upper);
}

bool RevolutePhysicsJoint::isMotorEnabled() const
{
  return getInternalJoint<b2RevoluteJoint>()->IsMotorEnabled();
}

void RevolutePhysicsJoint::enableMotor(bool enable)
{
  getInternalJoint<b2RevoluteJoint>()->EnableMotor(enable);
}

void RevolutePhysicsJoint::setMotorSpeed(float speed)
{
  getInternalJoint<b2RevoluteJoint>()->SetMotorSpeed(speed);
}

float RevolutePhysicsJoint::getMotorSpeed() const
{
  return getInternalJoint<b2RevoluteJoint>()->GetMotorSpeed();
}

void RevolutePhysicsJoint::setMaxMotorTorque(float torque)
{
  getInternalJoint<b2RevoluteJoint>()->SetMaxMotorTorque(torque);
}

float RevolutePhysicsJoint::getMaxMotorTorque() const
{
  return getInternalJoint<b2RevoluteJoint>()->GetMaxMotorTorque();
}

float RevolutePhysicsJoint::getMotorTorque(float inv_dt) const
{
  return getInternalJoint<b2RevoluteJoint>()->GetMotorTorque(inv_dt);
}

sf::Vector2f RevolutePhysicsJoint::getFirstAnchor() const
{
  // TODO //
}

sf::Vector2f RevolutePhysicsJoint::getSecondAnchor() const
{
  // TODO //
}

sf::Vector2f RevolutePhysicsJoint::getReactionForce(float inv_dt) const
{
  // TODO //
}

float RevolutePhysicsJoint::getReactionTorque(float inv_dt) const
{
  // TODO //
}

std::unique_ptr<b2JointDef> RevolutePhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_revolute_joint_def = std::make_unique<b2RevoluteJointDef>();
  b2_revolute_joint_def->Initialize(b2_first_physics_body, b2_second_physics_body,
                                    priv::PhysicsHelper::pixel_to_meter(m_anchor));

  return b2_revolute_joint_def;
}

/* -------------------------------- WeldPhysicsJoint ------------------------ */

WeldPhysicsJoint::WeldPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                   const sf::Vector2f& anchor) :
  PhysicsJoint(Type::Weld, first_physics_body, second_physics_body),
  m_anchor(anchor)
{

}

float WeldPhysicsJoint::getReferenceAngle() const
{
  return getInternalJoint<b2WeldJoint>()->GetReferenceAngle();
}

void WeldPhysicsJoint::setStiffness(float hz)
{
  getInternalJoint<b2WeldJoint>()->SetStiffness(hz);
}

float WeldPhysicsJoint::getStiffness() const
{
  return getInternalJoint<b2WeldJoint>()->GetStiffness();
}

sf::Vector2f WeldPhysicsJoint::getFirstAnchor() const
{
  // TODO //
}

sf::Vector2f WeldPhysicsJoint::getSecondAnchor() const
{
  // TODO //
}

sf::Vector2f WeldPhysicsJoint::getReactionForce(float inv_dt) const
{
  // TODO //
}

float WeldPhysicsJoint::getReactionTorque(float inv_dt) const
{
  // TODO //
}

std::unique_ptr<b2JointDef> WeldPhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_weld_joint_def = std::make_unique<b2WeldJointDef>();
  b2_weld_joint_def->Initialize(b2_first_physics_body, b2_second_physics_body,
                                priv::PhysicsHelper::pixel_to_meter(m_anchor));

  return b2_weld_joint_def;
}

/* ------------------------------- WheelPhysicsJoint ------------------------ */

WheelPhysicsJoint::WheelPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                     const sf::Vector2f& anchor, const sf::Vector2f& axis) :
  PhysicsJoint(Type::Wheel, first_physics_body, second_physics_body),
  m_anchor(anchor),
  m_axis(axis)
{

}

float WheelPhysicsJoint::getJointTranslation() const
{
  return getInternalJoint<b2WheelJoint>()->GetJointTranslation();
}

float WheelPhysicsJoint::getJointLinearSpeed() const
{
  return getInternalJoint<b2WheelJoint>()->GetJointLinearSpeed();
}

float WheelPhysicsJoint::getJointAngle() const
{
  return getInternalJoint<b2WheelJoint>()->GetJointAngle();
}

float WheelPhysicsJoint::getJointAngularSpeed() const
{
  return getInternalJoint<b2WheelJoint>()->GetJointAngularSpeed();
}

bool WheelPhysicsJoint::isLimitEnabled() const
{
  return getInternalJoint<b2WheelJoint>()->IsLimitEnabled();
}

void WheelPhysicsJoint::enableLimit(bool enable)
{
  getInternalJoint<b2WheelJoint>()->EnableLimit(enable);
}

float WheelPhysicsJoint::getLowerLimit() const
{
  return getInternalJoint<b2WheelJoint>()->GetLowerLimit();
}

float WheelPhysicsJoint::getUpperLimit() const
{
  return getInternalJoint<b2WheelJoint>()->GetUpperLimit();
}

void WheelPhysicsJoint::setLimits(float lower, float upper)
{
  getInternalJoint<b2WheelJoint>()->SetLimits(lower, upper);
}

bool WheelPhysicsJoint::isMotorEnabled() const
{
  return getInternalJoint<b2WheelJoint>()->IsMotorEnabled();
}

void WheelPhysicsJoint::enableMotor(bool enable)
{
  getInternalJoint<b2WheelJoint>()->EnableMotor(enable);
}

void WheelPhysicsJoint::setMotorSpeed(float speed)
{
  getInternalJoint<b2WheelJoint>()->SetMotorSpeed(speed);
}

float WheelPhysicsJoint::getMotorSpeed() const
{
  return getInternalJoint<b2WheelJoint>()->GetMotorSpeed();
}

void WheelPhysicsJoint::setMaxMotorTorque(float torque)
{
  getInternalJoint<b2WheelJoint>()->SetMaxMotorTorque(torque);
}

float WheelPhysicsJoint::getMaxMotorTorque() const
{
  return getInternalJoint<b2WheelJoint>()->GetMaxMotorTorque();
}

float WheelPhysicsJoint::getMotorTorque(float inv_dt)
{
  return getInternalJoint<b2WheelJoint>()->GetMotorTorque(inv_dt);
}

void WheelPhysicsJoint::setStiffness(float stiffness)
{
  getInternalJoint<b2WheelJoint>()->SetStiffness(stiffness);
}

float WheelPhysicsJoint::getStiffness() const
{
  return getInternalJoint<b2WheelJoint>()->GetStiffness();
}

void WheelPhysicsJoint::setDamping(float damping)
{
  getInternalJoint<b2WheelJoint>()->SetDamping(damping);
}

float WheelPhysicsJoint::getDamping() const
{
  return getInternalJoint<b2WheelJoint>()->GetDamping();
}

sf::Vector2f WheelPhysicsJoint::getFirstAnchor() const
{
  // TODO //
}

sf::Vector2f WheelPhysicsJoint::getSecondAnchor() const
{
  // TODO //
}

sf::Vector2f WheelPhysicsJoint::getReactionForce(float inv_dt) const
{
  // TODO //
}

float WheelPhysicsJoint::getReactionTorque(float inv_dt) const
{
  // TODO //
}

std::unique_ptr<b2JointDef> WheelPhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_wheel_joint_def = std::make_unique<b2WheelJointDef>();
  b2_wheel_joint_def->Initialize(b2_first_physics_body, b2_second_physics_body,
                                 priv::PhysicsHelper::pixel_to_meter(m_anchor),
                                 priv::PhysicsHelper::pixel_to_meter(m_axis));

  return b2_wheel_joint_def;
}



} // namespace egnim::physics