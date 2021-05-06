/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_joint.h>
#include <egnim/engine/physics/physics_body.h>
#include <egnim/engine/physics/physics_world.h>
#include <egnim/engine/physics/priv/b2_physics_casters.h>
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

/* ---------------------------------- PhysicsJoint -------------------------- */

PhysicsJoint::PhysicsJoint(Type type, PhysicsBody &first_physics_body, PhysicsBody &second_physics_body) :
  m_type(type),
  m_physics_world(*first_physics_body.getPhysicsWorld()),
  m_first_physics_body(first_physics_body),
  m_second_physics_body(second_physics_body),
  m_b2_joint(nullptr)
{
  assert(first_physics_body.getPhysicsWorld() == second_physics_body.getPhysicsWorld());
}

PhysicsJoint::~PhysicsJoint()
{
  destroyInternalJoint();
}

void PhysicsJoint::createInternalJoint()
{
  destroyInternalJoint();

  auto b2_joint_def = createInternalJointDef(m_first_physics_body.getInternalBody(),
                                             m_second_physics_body.getInternalBody());
  b2_joint_def->userData.pointer = reinterpret_cast<uintptr_t>(this);

  m_b2_joint = getPhysicsWorld()->createInternalJoint(b2_joint_def.get());

  getPhysicsWorld()->attachPhysicsJoint(this);
  getFirstPhysicsBody()->attachPhysicsJoint(this);
  getSecondPhysicsBody()->attachPhysicsJoint(this);
}

void PhysicsJoint::destroyInternalJoint()
{
  if (m_b2_joint)
  {
    getPhysicsWorld()->destroyInternalJoint(m_b2_joint);

    getPhysicsWorld()->detachPhysicsJoint(this);
    getFirstPhysicsBody()->detachPhysicsJoint(this);
    getSecondPhysicsBody()->detachPhysicsJoint(this);

    m_b2_joint = nullptr;
  }
}

const PhysicsBody* PhysicsJoint::getFirstPhysicsBody() const
{
  return std::addressof(m_first_physics_body);
}

PhysicsBody* PhysicsJoint::getFirstPhysicsBody()
{
  return std::addressof(m_first_physics_body);
}

const PhysicsBody* PhysicsJoint::getSecondPhysicsBody() const
{
  return std::addressof(m_second_physics_body);
}

PhysicsBody* PhysicsJoint::getSecondPhysicsBody()
{
  return std::addressof(m_second_physics_body);
}

const PhysicsWorld* PhysicsJoint::getPhysicsWorld() const
{
  return std::addressof(m_physics_world);
}

PhysicsWorld* PhysicsJoint::getPhysicsWorld()
{
  return std::addressof(m_physics_world);
}

sf::Vector2f PhysicsJoint::getFirstAnchor() const
{
  assert(m_b2_joint);
  return priv::b2_meter_to_pixel(m_b2_joint->GetAnchorA());
}

sf::Vector2f PhysicsJoint::getSecondAnchor() const
{
  assert(m_b2_joint);
  return priv::b2_meter_to_pixel(m_b2_joint->GetAnchorB());
}

sf::Vector2f PhysicsJoint::getReactionForce(float inv_dt) const
{
  assert(m_b2_joint);
  auto reaction_force = m_b2_joint->GetReactionForce(inv_dt);
  return sf::Vector2f(reaction_force.x, reaction_force.y);
}

float PhysicsJoint::getReactionTorque(float inv_dt) const
{
  assert(m_b2_joint);
  return m_b2_joint->GetReactionTorque(inv_dt);
}

PhysicsJoint::Type PhysicsJoint::getType() const
{
  return m_type;
}

/* ------------------------------ DistancePhysicsJoint ---------------------- */

DistancePhysicsJoint::DistancePhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                           const sf::Vector2f& first_anchor, const sf::Vector2f& second_anchor) :
  PhysicsJoint(Type::Distance, first_physics_body, second_physics_body),
  m_first_anchor(first_anchor),
  m_second_anchor(second_anchor)
{
  createInternalJoint();
}

void DistancePhysicsJoint::setLength(float length)
{
  getInternalJoint<b2DistanceJoint>()->SetLength(priv::b2_pixel_to_meter(length));
}

float DistancePhysicsJoint::getLength() const
{
  return priv::b2_meter_to_pixel(getInternalJoint<b2DistanceJoint>()->GetLength());
}

void DistancePhysicsJoint::setMinLength(float min_length)
{
  getInternalJoint<b2DistanceJoint>()->SetMinLength(priv::b2_pixel_to_meter(min_length));
}

float DistancePhysicsJoint::getMinLength() const
{
  return priv::b2_meter_to_pixel(getInternalJoint<b2DistanceJoint>()->GetMinLength());
}

void DistancePhysicsJoint::setMaxLength(float max_length)
{
  getInternalJoint<b2DistanceJoint>()->SetMaxLength(priv::b2_pixel_to_meter(max_length));
}

float DistancePhysicsJoint::getMaxLength() const
{
  return priv::b2_meter_to_pixel(getInternalJoint<b2DistanceJoint>()->GetMaxLength());
}

float DistancePhysicsJoint::getCurrentLength() const
{
  return priv::b2_meter_to_pixel(getInternalJoint<b2DistanceJoint>()->GetCurrentLength());
}

void DistancePhysicsJoint::setStiffness(float stiffness)
{
  getInternalJoint<b2DistanceJoint>()->SetStiffness(stiffness);
}

float DistancePhysicsJoint::getStiffness() const
{
  return getInternalJoint<b2DistanceJoint>()->GetStiffness();
}

void DistancePhysicsJoint::setDamping(float damping)
{
  getInternalJoint<b2DistanceJoint>()->SetDamping(damping);
}

float DistancePhysicsJoint::getDamping() const
{
  return getInternalJoint<b2DistanceJoint>()->GetDamping();
}

std::unique_ptr<b2JointDef> DistancePhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_distance_joint_def = std::make_unique<b2DistanceJointDef>();
  b2_distance_joint_def->Initialize(b2_first_physics_body, b2_second_physics_body,
                                    priv::b2_pixel_to_meter(m_first_anchor),
                                    priv::b2_pixel_to_meter(m_second_anchor));

  return b2_distance_joint_def;
}

/* ------------------------------ FrictionPhysicsJoint ---------------------- */

FrictionPhysicsJoint::FrictionPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                           const sf::Vector2f& anchor) :
  PhysicsJoint(Type::Friction, first_physics_body, second_physics_body),
  m_anchor(anchor)
{
  createInternalJoint();
}

const sf::Vector2f& FrictionPhysicsJoint::getAnchor() const
{
  return m_anchor;
}

void FrictionPhysicsJoint::setMaxForce(float force)
{
  getInternalJoint<b2FrictionJoint>()->SetMaxForce(force);
}

float FrictionPhysicsJoint::getMaxForce() const
{
  return getInternalJoint<b2FrictionJoint>()->GetMaxForce();
}

void FrictionPhysicsJoint::setMaxTorque(float torque)
{
  getInternalJoint<b2FrictionJoint>()->SetMaxTorque(torque);
}

float FrictionPhysicsJoint::getMaxTorque() const
{
  return getInternalJoint<b2FrictionJoint>()->GetMaxTorque();
}

std::unique_ptr<b2JointDef> FrictionPhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_friction_joint_def = std::make_unique<b2FrictionJointDef>();
  b2_friction_joint_def->Initialize(b2_first_physics_body, b2_second_physics_body,
                                    priv::b2_pixel_to_meter(m_anchor));

  return b2_friction_joint_def;
}

/* -------------------------------- MotorPhysicsJoint ----------------------- */

MotorPhysicsJoint::MotorPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body) :
  PhysicsJoint(Type::Motor, first_physics_body, second_physics_body)
{
  createInternalJoint();
}

void MotorPhysicsJoint::setMaxForce(float force)
{
  getInternalJoint<b2MotorJoint>()->SetMaxForce(force);
}

float MotorPhysicsJoint::getMaxForce() const
{
  return getInternalJoint<b2MotorJoint>()->GetMaxForce();
}

void MotorPhysicsJoint::setMaxTorque(float torque)
{
  getInternalJoint<b2MotorJoint>()->SetMaxTorque(torque);
}

float MotorPhysicsJoint::getMaxTorque() const
{
  return getInternalJoint<b2MotorJoint>()->GetMaxTorque();
}

void MotorPhysicsJoint::setCorrectionFactory(float factory)
{
  getInternalJoint<b2MotorJoint>()->SetCorrectionFactor(factory);
}

float MotorPhysicsJoint::getCorrectionFactory() const
{
  return getInternalJoint<b2MotorJoint>()->GetCorrectionFactor();
}

void MotorPhysicsJoint::setLinearOffset(const sf::Vector2f& linear_offset)
{
  getInternalJoint<b2MotorJoint>()->SetLinearOffset(b2Vec2(linear_offset.x, linear_offset.y));
}

sf::Vector2f MotorPhysicsJoint::getLinearOffset() const
{
  auto linear_offset = getInternalJoint<b2MotorJoint>()->GetLinearOffset();
  return sf::Vector2f(linear_offset.x, linear_offset.y);
}

void MotorPhysicsJoint::setAngularOffset(float angular_offset)
{
  getInternalJoint<b2MotorJoint>()->SetAngularOffset(angular_offset);
}

float MotorPhysicsJoint::getAngularOffset() const
{
  return getInternalJoint<b2MotorJoint>()->GetAngularOffset();
}

std::unique_ptr<b2JointDef> MotorPhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_motor_joint_def = std::make_unique<b2MotorJointDef>();
  b2_motor_joint_def->Initialize(b2_first_physics_body, b2_second_physics_body);

  return b2_motor_joint_def;
}

/* ------------------------------ PrismaticPhysicsJoint --------------------- */

PrismaticPhysicsJoint::PrismaticPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                             const sf::Vector2f& anchor, const sf::Vector2f& axis) :
  PhysicsJoint(Type::Prismatic, first_physics_body, second_physics_body),
  m_anchor(anchor),
  m_axis(axis)
{
  createInternalJoint();
}

float PrismaticPhysicsJoint::getReferenceAngle() const
{
  return getInternalJoint<b2PrismaticJoint>()->GetReferenceAngle();
}

float PrismaticPhysicsJoint::getJointTranslation() const
{
  return getInternalJoint<b2PrismaticJoint>()->GetJointTranslation();
}

float PrismaticPhysicsJoint::getJointSpeed() const
{
  return getInternalJoint<b2PrismaticJoint>()->GetJointSpeed();
}

bool PrismaticPhysicsJoint::isLimitEnabled() const
{
  return getInternalJoint<b2PrismaticJoint>()->IsLimitEnabled();
}

void PrismaticPhysicsJoint::enableLimit(bool enable)
{
  getInternalJoint<b2PrismaticJoint>()->EnableLimit(enable);
}

float PrismaticPhysicsJoint::getLowerLimit() const
{
  return getInternalJoint<b2PrismaticJoint>()->GetLowerLimit();
}

float PrismaticPhysicsJoint::getUpperLimit() const
{
  return getInternalJoint<b2PrismaticJoint>()->GetUpperLimit();
}

void PrismaticPhysicsJoint::setLimits(float lower, float upper)
{
  getInternalJoint<b2PrismaticJoint>()->SetLimits(lower, upper);
}

bool PrismaticPhysicsJoint::isMotorEnabled() const
{
  return getInternalJoint<b2PrismaticJoint>()->IsMotorEnabled();
}

void PrismaticPhysicsJoint::enableMotor(bool enable)
{
  getInternalJoint<b2PrismaticJoint>()->EnableMotor(enable);
}

void PrismaticPhysicsJoint::setMotorSpeed(float speed)
{
  getInternalJoint<b2PrismaticJoint>()->SetMotorSpeed(speed);
}

float PrismaticPhysicsJoint::getMotorSpeed() const
{
  return getInternalJoint<b2PrismaticJoint>()->GetMotorSpeed();
}

void PrismaticPhysicsJoint::setMaxMotorForce(float force)
{
  getInternalJoint<b2PrismaticJoint>()->SetMaxMotorForce(force);
}

float PrismaticPhysicsJoint::getMaxMotorForce() const
{
  return getInternalJoint<b2PrismaticJoint>()->GetMaxMotorForce();
}

float PrismaticPhysicsJoint::getMotorForce(float inv_dt) const
{
  return getInternalJoint<b2PrismaticJoint>()->GetMotorForce(inv_dt);
}

std::unique_ptr<b2JointDef> PrismaticPhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_prismatic_joint_def = std::make_unique<b2PrismaticJointDef>();
  b2_prismatic_joint_def->Initialize(b2_first_physics_body, b2_second_physics_body,
                                     priv::b2_pixel_to_meter(m_anchor),
                                     priv::b2_pixel_to_meter(m_axis));

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
  createInternalJoint();
}

sf::Vector2f PulleyPhysicsJoint::getFirstGroundAnchor() const
{
  auto first_ground_anchor = getInternalJoint<b2PulleyJoint>()->GetGroundAnchorA();
  return priv::b2_meter_to_pixel(first_ground_anchor);
}

sf::Vector2f PulleyPhysicsJoint::getSecondGroundAnchor() const
{
  auto second_ground_anchor = getInternalJoint<b2PulleyJoint>()->GetGroundAnchorB();
  return priv::b2_meter_to_pixel(second_ground_anchor);
}

float PulleyPhysicsJoint::getFirstLength() const
{
  return priv::b2_meter_to_pixel(getInternalJoint<b2PulleyJoint>()->GetLengthA());
}

float PulleyPhysicsJoint::getSecondLength() const
{
  return priv::b2_meter_to_pixel(getInternalJoint<b2PulleyJoint>()->GetLengthB());
}

float PulleyPhysicsJoint::getRation() const
{
  return getInternalJoint<b2PulleyJoint>()->GetRatio();
}

float PulleyPhysicsJoint::getCurrentFirstLength() const
{
  return priv::b2_meter_to_pixel(getInternalJoint<b2PulleyJoint>()->GetCurrentLengthA());
}

float PulleyPhysicsJoint::getCurrentSecondLength() const
{
  return priv::b2_meter_to_pixel(getInternalJoint<b2PulleyJoint>()->GetCurrentLengthB());
}

std::unique_ptr<b2JointDef> PulleyPhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_pulley_joint_def = std::make_unique<b2PulleyJointDef>();
  b2_pulley_joint_def->Initialize(b2_first_physics_body, b2_second_physics_body,
                                  priv::b2_pixel_to_meter(m_first_ground_anchor),
                                  priv::b2_pixel_to_meter(m_second_ground_anchor),
                                  priv::b2_pixel_to_meter(m_first_anchor),
                                  priv::b2_pixel_to_meter(m_second_anchor),
                                  m_ration);

  return b2_pulley_joint_def;
}

/* ------------------------------ RevolutePhysicsJoint ---------------------- */

RevolutePhysicsJoint::RevolutePhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                           const sf::Vector2f& anchor) :
  PhysicsJoint(Type::Revolute, first_physics_body, second_physics_body),
  m_anchor(anchor)
{
  createInternalJoint();
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

std::unique_ptr<b2JointDef> RevolutePhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_revolute_joint_def = std::make_unique<b2RevoluteJointDef>();
  b2_revolute_joint_def->Initialize(b2_first_physics_body, b2_second_physics_body,
                                    priv::b2_pixel_to_meter(m_anchor));

  return b2_revolute_joint_def;
}

/* -------------------------------- WeldPhysicsJoint ------------------------ */

WeldPhysicsJoint::WeldPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                   const sf::Vector2f& anchor) :
  PhysicsJoint(Type::Weld, first_physics_body, second_physics_body),
  m_anchor(anchor)
{
  createInternalJoint();
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

std::unique_ptr<b2JointDef> WeldPhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_weld_joint_def = std::make_unique<b2WeldJointDef>();
  b2_weld_joint_def->Initialize(b2_first_physics_body, b2_second_physics_body,
                                priv::b2_pixel_to_meter(m_anchor));

  return b2_weld_joint_def;
}

/* ------------------------------- WheelPhysicsJoint ------------------------ */

WheelPhysicsJoint::WheelPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                     const sf::Vector2f& anchor, const sf::Vector2f& axis) :
  PhysicsJoint(Type::Wheel, first_physics_body, second_physics_body),
  m_anchor(anchor),
  m_axis(axis)
{
  createInternalJoint();
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

std::unique_ptr<b2JointDef> WheelPhysicsJoint::createInternalJointDef(
  b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const
{
  auto b2_wheel_joint_def = std::make_unique<b2WheelJointDef>();
  b2_wheel_joint_def->Initialize(b2_first_physics_body, b2_second_physics_body,
                                 priv::b2_pixel_to_meter(m_anchor),
                                 priv::b2_pixel_to_meter(m_axis));

  return b2_wheel_joint_def;
}



} // namespace egnim::physics