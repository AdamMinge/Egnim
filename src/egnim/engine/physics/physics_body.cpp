/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_body.h>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_body.h>
#include <egnim/engine/physics/physics_world.h>
#include <egnim/engine/physics/physics_shape.h>
#include <egnim/engine/scene/node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

PhysicsBody::PhysicsBody(PhysicsWorld& physics_world, Type type) :
  m_physics_world(physics_world),
  m_b2_body(createInternalBody(type))
{

}

PhysicsBody::~PhysicsBody()
{
  destroyInternalBody();
}

void PhysicsBody::setPosition(const sf::Vector2f& position)
{
  auto b2_body_angle = m_b2_body->GetAngle();
  m_b2_body->SetTransform(b2Vec2(position.x, position.y), b2_body_angle);
}

sf::Vector2f PhysicsBody::getPosition() const
{
  auto b2_body_pos = m_b2_body->GetPosition();
  return sf::Vector2f(b2_body_pos.x, b2_body_pos.y);
}

void PhysicsBody::setRotation(float angle)
{
  auto b2_body_pos = m_b2_body->GetPosition();
  m_b2_body->SetTransform(b2_body_pos, angle);
}

float PhysicsBody::getRotation() const
{
  return m_b2_body->GetAngle();
}

void PhysicsBody::update(sf::Time dt)
{

}

PhysicsWorld& PhysicsBody::getPhysicsWorld()
{
  return m_physics_world;
}

const PhysicsWorld& PhysicsBody::getPhysicsWorld() const
{
  return m_physics_world;
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
  physics_shape->setPhysicsBody(this);
  m_physics_shapes.push_back(std::move(physics_shape));
}

std::unique_ptr<PhysicsShape> PhysicsBody::detachPhysicsShape(const PhysicsShape& physics_shape)
{
  auto found = std::find_if(m_physics_shapes.begin(), m_physics_shapes.end(), [&physics_shape](auto &shape)
  {
    return shape.get() == &physics_shape;
  });

  if (found == m_physics_shapes.end())
    return nullptr;

  auto shape = std::move(*found);
  shape->setPhysicsBody(nullptr);
  m_physics_shapes.erase(found);
  return shape;
}

const std::vector<std::unique_ptr<PhysicsShape>>& PhysicsBody::getPhysicsShapes() const
{
  return m_physics_shapes;
}

b2Body* PhysicsBody::createInternalBody(Type type)
{
  destroyInternalBody();

  b2BodyDef body_def;
  body_def.type = static_cast<b2BodyType>(type);
  body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

  return getPhysicsWorld().createInternalBody(&body_def);;
}

void PhysicsBody::destroyInternalBody()
{
  getPhysicsWorld().destroyInternalBody(m_b2_body);
  m_b2_body = nullptr;
}

void PhysicsBody::beforeSimulation()
{
  if(!getOwner()) return;

  auto world_pos = getOwner()->getWorldPosition();
  auto world_rotate = getOwner()->getWorldRotation();

  setPosition(world_pos);
  setRotation(world_rotate);
}

void PhysicsBody::afterSimulation()
{
  if(!getOwner()) return;

  auto owner_pos = getPosition();
  auto owner_rotate = getRotation();

  if(auto owner_parent = getOwner()->getParent(); owner_parent)
  {
    owner_pos = owner_parent->getTransform().getInverse().transformPoint(owner_pos);
    owner_rotate -= owner_parent->getRotation();
  }

  getOwner()->setPosition(owner_pos);
  getOwner()->setRotation(owner_rotate);
}

b2Fixture* PhysicsBody::createInternalFixture(const b2FixtureDef* b2_fixture_def)
{
  return m_b2_body->CreateFixture(b2_fixture_def);
}

void PhysicsBody::destroyInternalFixture(b2Fixture* b2_fixture)
{
  m_b2_body->DestroyFixture(b2_fixture);
}

} // namespace egnim::physics