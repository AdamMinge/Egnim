/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_world.h>
#include <egnim/engine/physics/physics_body.h>
#include <egnim/engine/scene/scene_node.h>
#include <egnim/engine/scene/node.h>
/* --------------------------------- Standard ------------------------------- */
#include <queue>
#include <list>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

PhysicsWorld::PhysicsWorld(scene::SceneNode& scene_node, const sf::Vector2f& gravity) :
  m_scene_node(scene_node),
  m_b2_world(std::make_unique<b2World>(b2Vec2(gravity.x, gravity.y)))
{

}

PhysicsWorld::~PhysicsWorld() = default;

void PhysicsWorld::update(float time_step, int32_t velocity_iterations, int32_t position_iterations)
{
  beforeSimulation();
  m_b2_world->Step(time_step, velocity_iterations, position_iterations);
  afterSimulation();
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

b2Body* PhysicsWorld::createInternalBody(const b2BodyDef* b2_body_def)
{
  return m_b2_world->CreateBody(b2_body_def);
}

void PhysicsWorld::destroyInternalBody(b2Body* b2_body)
{
  m_b2_world->DestroyBody(b2_body);
}

void PhysicsWorld::beforeSimulation()
{
  std::queue<scene::Node*> nodes;
  nodes.push(std::addressof(m_scene_node));

  while(nodes.empty())
  {
    auto current_node = nodes.front();
    nodes.pop();

    if(auto physics_body = current_node->getPhysicsBody(); physics_body)
      physics_body->beforeSimulation();

    auto& children = current_node->getChildren();
    for(auto& child : children)
      nodes.push(child.get());
  }
}

void PhysicsWorld::afterSimulation()
{
  std::queue<scene::Node*> nodes;
  nodes.push(std::addressof(m_scene_node));

  while(nodes.empty())
  {
    auto current_node = nodes.front();
    nodes.pop();

    if(auto physics_body = current_node->getPhysicsBody(); physics_body)
      physics_body->afterSimulation();

    auto& children = current_node->getChildren();
    for(auto& child : children)
      nodes.push(child.get());
  }
}

b2Joint* PhysicsWorld::createInternalJoint(const b2JointDef* b2_joint_def)
{
  return m_b2_world->CreateJoint(b2_joint_def);
}

void PhysicsWorld::destroyInternalJoint(b2Joint* b2_joint)
{
  return m_b2_world->DestroyJoint(b2_joint);
}

} // namespace egnim::physics
