/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_world.h>
#include <egnim/engine/physics/physics_body.h>
#include <egnim/engine/scene/node.h>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
#include <list>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

PhysicsWorld::PhysicsWorld(const sf::Vector2f& gravity) :
  m_b2_world(std::make_unique<b2World>(b2Vec2(gravity.x, gravity.y)))
{

}

PhysicsWorld::~PhysicsWorld() = default;

void PhysicsWorld::update(float time_step, int32_t velocity_iterations, int32_t position_iterations)
{
  auto bodies = getPhysicsBody();

  for(auto& body : bodies)
    body->beforeSimulation();

  m_b2_world->Step(time_step, velocity_iterations, position_iterations);

  for(auto& body : bodies)
    body->afterSimulation();
}

void PhysicsWorld::setGravity(const sf::Vector2f& gravity)
{
  m_b2_world->SetGravity(b2Vec2(gravity.x, gravity.y));
}

sf::Vector2f PhysicsWorld::getGravity() const
{
  auto b2_vec = m_b2_world->GetGravity();
  return sf::Vector2f(b2_vec.x, b2_vec.y);
}

b2Body* PhysicsWorld::createBody(const b2BodyDef* b2_body_def)
{
  auto b2_body = m_b2_world->CreateBody(b2_body_def);
  return b2_body;
}

void PhysicsWorld::destroyBody(b2Body* b2_body)
{
  m_b2_world->DestroyBody(b2_body);
}

std::list<PhysicsBody*> PhysicsWorld::getPhysicsBody()
{
  std::list<PhysicsBody*> physicsBodies;
  for(auto b2_body= m_b2_world->GetBodyList(); b2_body != nullptr; b2_body = b2_body->GetNext())
  {
    auto b2_body_user_data = b2_body->GetUserData().pointer;
    assert(b2_body_user_data != reinterpret_cast<uintptr_t>(nullptr));
    physicsBodies.push_back(reinterpret_cast<PhysicsBody*>(b2_body_user_data));
  }

  physicsBodies.sort([](auto first, auto second){
    assert(first->getOwner());
    assert(second->getOwner());

    auto current_node = second->getOwner();
    while(current_node->getParent() && current_node != first->getOwner())
      current_node = current_node->getParent();

    return current_node == first->getOwner();
  });

  return physicsBodies;
}

} // namespace egnim::physics
