/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_body.h>
#include <box2d/b2_joint.h>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_body.h>
#include <egnim/engine/physics/physics_world.h>
#include <egnim/engine/physics/physics_shape.h>
#include <egnim/engine/physics/priv/physics_helper.h>
#include <egnim/engine/scene/node.h>
#include <egnim/engine/scene/scene_node.h>
#include <egnim/engine/scene/scene_visitor.h>
#include <egnim/engine/core/unique_pointer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

#define PushPostProcessProperties(Setter, value, postprocess_value, properties)                         \
do {                                                                                                    \
  if(m_b2_body)                                                                                         \
    { m_b2_body->Setter(postprocess_value); }                                                           \
  else                                                                                                  \
  {                                                                                                     \
    delay([this, value](){ m_b2_body->Setter(postprocess_value); });                                    \
    (properties) = value;                                                                               \
  }                                                                                                     \
                                                                                                        \
} while(false)

#define PushProperties(Setter, value, properties)                                                       \
PushPostProcessProperties(Setter, value, value, properties)

#define PullProperties(Getter, properties)                                                              \
do {                                                                                                    \
  if(m_b2_body)                                                                                         \
    { return m_b2_body->Getter(); }                                                                     \
  else                                                                                                  \
    { return properties; }                                                                              \
} while(false)

#define PullPostProcessProperties(Getter, properties, postprocess)                                      \
do {                                                                                                    \
  if(m_b2_body)                                                                                         \
    { return postprocess(m_b2_body->Getter()); }                                                        \
  else                                                                                                  \
    { return properties; }                                                                              \
} while(false)

/* -------------------------------- PhysicsBody ----------------------------- */

PhysicsBody::PhysicsBody() :
  m_type(Type::DynamicBody),
  m_physics_world(nullptr),
  m_b2_body(nullptr),
  m_linear_velocity(sf::Vector2f(0.f, 0.f)),
  m_angular_velocity(0.f),
  m_linear_damping(0.f),
  m_angular_damping(0.f),
  m_gravity_scale(1.f),
  m_bullet(false),
  m_fixed_rotation(false),
  m_awake(true),
  m_enabled(true)
{

}

PhysicsBody::~PhysicsBody()
{
  destroyInternalBody();
}

PhysicsWorld* PhysicsBody::getPhysicsWorld()
{
  return m_physics_world;
}

const PhysicsWorld* PhysicsBody::getPhysicsWorld() const
{
  return m_physics_world;
}

void PhysicsBody::setLinearVelocity(const sf::Vector2f& linear_velocity)
{
  PushPostProcessProperties(SetLinearVelocity, linear_velocity,
                            priv::PhysicsHelper::cast(linear_velocity), m_linear_velocity);
}

sf::Vector2f PhysicsBody::getLinearVelocity() const
{
  PullPostProcessProperties(GetLinearVelocity, m_linear_velocity,  priv::PhysicsHelper::cast);
}

void PhysicsBody::setAngularVelocity(float omega)
{
  PushProperties(SetAngularVelocity, omega, m_angular_velocity);
}

float PhysicsBody::getAngularVelocity() const
{
  PullProperties(GetAngularVelocity, m_angular_velocity);
}

void PhysicsBody::applyForce(const sf::Vector2f& force, const sf::Vector2f& point, bool awake)
{
  if(m_b2_body)
    m_b2_body->ApplyForce(priv::PhysicsHelper::cast(force), priv::PhysicsHelper::cast(point), awake);
  else
    { delay([this, force, point, awake](){
      m_b2_body->ApplyForce(priv::PhysicsHelper::cast(force), priv::PhysicsHelper::cast(point), awake); }); }
}

void PhysicsBody::applyForceToCenter(const sf::Vector2f& force, bool awake)
{
  if(m_b2_body)
    m_b2_body->ApplyForceToCenter(priv::PhysicsHelper::cast(force), awake);
  else
  { delay([this, force, awake](){
      m_b2_body->ApplyForceToCenter(priv::PhysicsHelper::cast(force), awake); }); }
}

void PhysicsBody::applyTorque(float torque, bool awake)
{
  if(m_b2_body)
    m_b2_body->ApplyTorque(torque, awake);
  else
  { delay([this, torque, awake](){
      m_b2_body->ApplyTorque(torque, awake); }); }
}

void PhysicsBody::applyLinearImpulse(const sf::Vector2f& impulse, const sf::Vector2f& point, bool awake)
{
  if(m_b2_body)
    m_b2_body->ApplyLinearImpulse(priv::PhysicsHelper::cast(impulse), priv::PhysicsHelper::cast(point), awake);
  else
  { delay([this, impulse, point, awake](){
      m_b2_body->ApplyLinearImpulse(priv::PhysicsHelper::cast(impulse), priv::PhysicsHelper::cast(point), awake); }); }
}

void PhysicsBody::applyLinearImpulseToCenter(const sf::Vector2f& impulse, bool awake)
{
  if(m_b2_body)
    m_b2_body->ApplyLinearImpulseToCenter(priv::PhysicsHelper::cast(impulse), awake);
  else
  { delay([this, impulse, awake](){
      m_b2_body->ApplyLinearImpulseToCenter(priv::PhysicsHelper::cast(impulse), awake); }); }
}

void PhysicsBody::applyAngularImpulse(float impulse, bool awake)
{
  if(m_b2_body)
    m_b2_body->ApplyAngularImpulse(impulse, awake);
  else
  { delay([this, impulse, awake](){
      m_b2_body->ApplyAngularImpulse(impulse, awake); }); }
}

void PhysicsBody::resetMassInfo()
{

}

void PhysicsBody::setMassInfo(const PhysicsMassInfo& mass_info)
{

}

PhysicsMassInfo PhysicsBody::getMassInfo() const
{

}

float PhysicsBody::getMass() const
{

}

float PhysicsBody::getInertia() const
{

}

void PhysicsBody::setType(Type type)
{
  PushPostProcessProperties(SetType, type, static_cast<b2BodyType>(type), m_type);
}

PhysicsBody::Type PhysicsBody::getType() const
{
  PullPostProcessProperties(GetType, m_type, static_cast<Type>);
}

void PhysicsBody::setLinearDamping(float linear_damping)
{
  PushProperties(SetLinearDamping, linear_damping, m_linear_damping);
}

float PhysicsBody::getLinearDamping() const
{
  PullProperties(GetLinearDamping, m_linear_damping);
}

void PhysicsBody::setAngularDamping(float angular_damping)
{
  PushProperties(SetAngularDamping, angular_damping, m_angular_damping);;
}

float PhysicsBody::getAngularDamping() const
{
  PullProperties(GetAngularDamping, m_angular_damping);
}

void PhysicsBody::setBullet(bool bullet)
{
  PushProperties(SetBullet, bullet, m_bullet);
}

bool PhysicsBody::isBullet() const
{
  PullProperties(IsBullet, m_bullet);
}

void PhysicsBody::setGravityScale(float gravity_scale)
{
  PushProperties(SetGravityScale, gravity_scale, m_gravity_scale);
}

float PhysicsBody::getGravityScale() const
{
  PullProperties(GetGravityScale, m_gravity_scale);
}

void PhysicsBody::setFixedRotation(bool fixed)
{
  PushProperties(SetFixedRotation, fixed, m_fixed_rotation);
}

bool PhysicsBody::isFixedRotation() const
{
  PullProperties(IsFixedRotation, m_fixed_rotation);
}

void PhysicsBody::setAwake(bool awake)
{
  PushProperties(SetAwake, awake, m_awake);
}

bool PhysicsBody::isAwake() const
{
  PullProperties(IsAwake, m_awake);
}

void PhysicsBody::setEnabled(bool enabled)
{
  PushProperties(SetEnabled, enabled, m_enabled);
}

bool PhysicsBody::isEnabled() const
{
  PullProperties(IsEnabled, m_enabled);
}

void PhysicsBody::attachPhysicsShape(std::unique_ptr<PhysicsShape> physics_shape)
{
  m_physics_shapes.push_back(std::move(physics_shape));
}

std::unique_ptr<PhysicsShape> PhysicsBody::detachPhysicsShape(const PhysicsShape& physics_shape)
{
  auto found = std::find_if(m_physics_shapes.begin(), m_physics_shapes.end(), [&physics_shape](auto &shape)
  {
    return shape.get() == std::addressof(physics_shape);
  });

  if (found == m_physics_shapes.end())
    return nullptr;

  auto shape = std::move(*found);
  m_physics_shapes.erase(found);
  return shape;
}

const std::list<std::unique_ptr<PhysicsShape>>& PhysicsBody::getPhysicsShapes() const
{
  return m_physics_shapes;
}

const std::list<PhysicsJoint*>& PhysicsBody::getPhysicsJoints() const
{
  return m_physics_joints;
}

void PhysicsBody::accept(scene::SceneVisitor& visitor)
{
  visitor.visitPhysicsBody(*this);
}

void PhysicsBody::onEnter()
{
  auto scene_node = getScene();
  m_physics_world = scene_node ? std::addressof(scene_node->getPhysicsWorld()) : nullptr;

  createInternalBody();
  flushDelayTasks();

  Node::onEnter();
};

void PhysicsBody::onExit()
{
  destroyInternalBody();

  auto scene_node = getScene();
  m_physics_world = scene_node ? std::addressof(scene_node->getPhysicsWorld()) : nullptr;

  Node::onExit();
}

void PhysicsBody::attachPhysicsJoint(PhysicsJoint* physics_joint)
{
  m_physics_joints.push_back(physics_joint);
}
void PhysicsBody::detachPhysicsJoint(PhysicsJoint* physics_joint)
{
  auto found = std::find(m_physics_joints.begin(), m_physics_joints.end(), physics_joint);
  if (found != m_physics_joints.end())
    m_physics_joints.erase(found);
}

void PhysicsBody::createInternalBody()
{
  if(m_physics_world && !m_b2_body)
  {
    b2BodyDef body_def;
    body_def.type = static_cast<b2BodyType>(b2_dynamicBody);
    body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

    m_b2_body = getPhysicsWorld()->createInternalBody(&body_def);

    getPhysicsWorld()->attachPhysicsBody(this);
  }
}

void PhysicsBody::destroyInternalBody()
{
  if(m_physics_world && m_b2_body)
  {
    m_physics_shapes.clear();
    getPhysicsWorld()->destroyInternalBody(m_b2_body);
    getPhysicsWorld()->detachPhysicsBody(this);
    m_b2_body = nullptr;
  }
}

void PhysicsBody::beforeSimulation()
{
  auto world_pos = getWorldTransform().transformPoint(getOrigin());
  auto world_rotate = getWorldRotation();

  m_b2_body->SetTransform(priv::PhysicsHelper::pixel_to_meter(world_pos),
                          priv::PhysicsHelper::angleToRadian(world_rotate));
}

void PhysicsBody::afterSimulation()
{
  auto owner_pos = priv::PhysicsHelper::meter_to_pixel(m_b2_body->GetPosition());
  auto owner_rotate = priv::PhysicsHelper::radianToAngle(m_b2_body->GetAngle());

  if(auto owner_parent = getParent(); owner_parent)
  {
    owner_pos = owner_parent->getTransform().getInverse().transformPoint(owner_pos);
    owner_rotate -= owner_parent->getRotation();
  }

  setPosition(owner_pos);
  setRotation(owner_rotate);
}

b2Fixture* PhysicsBody::createInternalFixture(const b2FixtureDef* b2_fixture_def)
{
  return m_b2_body->CreateFixture(b2_fixture_def);
}

void PhysicsBody::destroyInternalFixture(b2Fixture* b2_fixture)
{
  m_b2_body->DestroyFixture(b2_fixture);
}

const b2Body* PhysicsBody::getInternalBody() const
{
  return m_b2_body;
}

b2Body* PhysicsBody::getInternalBody()
{
  return m_b2_body;
}

void PhysicsBody::delay(const DelayTask& task)
{
  m_delay_tasks.push_back(task);
}

void PhysicsBody::flushDelayTasks()
{
  for(auto& task : m_delay_tasks)
    task();
  m_delay_tasks.clear();
}

} // namespace egnim::physics