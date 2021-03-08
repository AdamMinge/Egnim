/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_body.h>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_body.h>
#include <egnim/engine/physics/physics_world.h>
#include <egnim/engine/scene/node.h>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

PhysicsBody::PhysicsBody(PhysicsWorld& physics_world) :
  m_physics_world(physics_world),
  m_b2_body(nullptr)
{

}

PhysicsBody::~PhysicsBody()
{
  destroyBody();
}

void PhysicsBody::setPosition(const sf::Vector2f& position)
{
  assert(m_b2_body);
  auto b2_body_angle = m_b2_body->GetAngle();
  m_b2_body->SetTransform(b2Vec2(position.x, position.y), b2_body_angle);
}

sf::Vector2f PhysicsBody::getPosition() const
{
  assert(m_b2_body);
  auto b2_body_pos = m_b2_body->GetPosition();
  return sf::Vector2f(b2_body_pos.x, b2_body_pos.y);
}

void PhysicsBody::setRotation(float angle)
{
  assert(m_b2_body);
  auto b2_body_pos = m_b2_body->GetPosition();
  m_b2_body->SetTransform(b2_body_pos, angle);
}

float PhysicsBody::getRotation() const
{
  assert(m_b2_body);
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

void PhysicsBody::createBody(const b2BodyDef& b2_body_def)
{
  destroyBody();

  auto body_def = b2_body_def;
  body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

  m_b2_body = getPhysicsWorld().createBody(&body_def);
}

void PhysicsBody::destroyBody()
{
  if(m_b2_body)
    m_physics_world.destroyBody(m_b2_body);

  m_b2_body = nullptr;
}

void PhysicsBody::beforeSimulation()
{
  assert(getOwner());
  auto world_pos = getOwner()->getWorldPosition();
  auto world_rotate = getOwner()->getWorldRotation();

  setPosition(world_pos);
  setRotation(world_rotate);

}

void PhysicsBody::afterSimulation()
{
  assert(getOwner());
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

} // namespace egnim::physics