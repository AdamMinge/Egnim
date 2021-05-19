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

PhysicsBody::PhysicsBody(Type type) :
  m_type(type),
  m_physics_world(nullptr),
  m_b2_body(nullptr)
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
  m_b2_body->SetLinearVelocity(priv::PhysicsHelper::pixel_to_meter(linear_velocity));
}

sf::Vector2f PhysicsBody::getLinearVelocity() const
{
  return priv::PhysicsHelper::meter_to_pixel(m_b2_body->GetLinearVelocity());
}

void PhysicsBody::setAngularVelocity(float omega)
{
  m_b2_body->SetAngularVelocity(omega);
}

float PhysicsBody::getAngularVelocity() const
{
  return m_b2_body->GetAngularVelocity();
}

void PhysicsBody::applyForce(const sf::Vector2f& force, const sf::Vector2f& point, bool awake)
{
  m_b2_body->ApplyForce(priv::PhysicsHelper::pixel_to_meter(force), priv::PhysicsHelper::pixel_to_meter(point), awake);
}

void PhysicsBody::applyForceToCenter(const sf::Vector2f& force, bool awake)
{
  m_b2_body->ApplyForceToCenter(priv::PhysicsHelper::pixel_to_meter(force), awake);
}

void PhysicsBody::applyTorque(float torque, bool awake)
{
  m_b2_body->ApplyTorque(torque, awake);
}

void PhysicsBody::applyLinearImpulse(const sf::Vector2f& impulse, const sf::Vector2f& point, bool awake)
{
  m_b2_body->ApplyLinearImpulse(priv::PhysicsHelper::pixel_to_meter(impulse),
                                priv::PhysicsHelper::pixel_to_meter(point), awake);
}

void PhysicsBody::applyLinearImpulseToCenter(const sf::Vector2f& impulse, bool awake)
{
  m_b2_body->ApplyLinearImpulseToCenter(priv::PhysicsHelper::pixel_to_meter(impulse), awake);
}

void PhysicsBody::applyAngularImpulse(float impulse, bool awake)
{
  m_b2_body->ApplyAngularImpulse(impulse, awake);
}

float PhysicsBody::getMass() const
{
  return m_b2_body->GetMass();
}

float PhysicsBody::getInertia() const
{
  return m_b2_body->GetInertia();
}

void PhysicsBody::setType(Type type)
{
  m_b2_body->SetType(static_cast<b2BodyType>(type));
}

PhysicsBody::Type PhysicsBody::getType() const
{
  return static_cast<PhysicsBody::Type>(m_b2_body->GetType());
}

void PhysicsBody::setLinearDamping(float linear_damping)
{
  m_b2_body->SetLinearDamping(linear_damping);
}

float PhysicsBody::getLinearDamping() const
{
  return m_b2_body->GetLinearDamping();
}

void PhysicsBody::setAngularDamping(float angular_damping)
{
  m_b2_body->SetAngularDamping(angular_damping);
}

float PhysicsBody::getAngularDamping() const
{
  return m_b2_body->GetAngularDamping();
}

void PhysicsBody::setBullet(bool bullet)
{
  m_b2_body->SetBullet(bullet);
}

bool PhysicsBody::isBullet() const
{
  return m_b2_body->IsBullet();
}

void PhysicsBody::setGravityScale(float gravity_scale)
{
  m_b2_body->SetGravityScale(gravity_scale);
}

float PhysicsBody::getGravityScale() const
{
  return m_b2_body->GetGravityScale();
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

void PhysicsBody::setAwake(bool awake)
{
  m_b2_body->SetAwake(awake);
}

bool PhysicsBody::isAwake() const
{
  return m_b2_body->IsAwake();
}

void PhysicsBody::setEnabled(bool enabled)
{
  m_b2_body->SetEnabled(enabled);
}

bool PhysicsBody::isEnabled() const
{
  return m_b2_body->IsEnabled();
}

void PhysicsBody::accept(scene::SceneVisitor& visitor)
{
  visitor.visitPhysicsBody(*this);
}

void PhysicsBody::onEnter()
{
  auto scene_node = getScene();
  m_physics_world = scene_node ? std::addressof(scene_node->getPhysicsWorld()) : nullptr;

  createInternalBody(m_type);
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

void PhysicsBody::createInternalBody(Type type)
{
  if(m_physics_world && !m_b2_body)
  {
    b2BodyDef body_def;
    body_def.type = static_cast<b2BodyType>(type);
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

} // namespace egnim::physics