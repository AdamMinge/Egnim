/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_world.h>
#include <egnim/engine/physics/physics_body.h>
#include <egnim/engine/scene/scene_node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

/* ----------------------------- PhysicsWorldCallback ----------------------- */

class PhysicsWorldCallback : public b2ContactListener
{
public:
  explicit PhysicsWorldCallback(core::CommandQueue& command_queue) : m_command_queue(command_queue) {}
  ~PhysicsWorldCallback() override = default;

  void BeginContact(b2Contact* contact) override;
  void EndContact(b2Contact* contact) override;
  void PreSolve(b2Contact* contact, const b2Manifold* old_manifold) override;
  void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

private:
  core::CommandQueue& m_command_queue;
};

void PhysicsWorldCallback::BeginContact(b2Contact* contact)
{

}

void PhysicsWorldCallback::EndContact(b2Contact* contact)
{

}

void PhysicsWorldCallback::PreSolve(b2Contact* contact, const b2Manifold* old_manifold)
{

}

void PhysicsWorldCallback::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}

/* --------------------------------- PhysicsWorld --------------------------- */

PhysicsWorld::PhysicsWorld(scene::SceneNode& scene_node, core::CommandQueue& command_queue, const sf::Vector2f& gravity) :
  m_scene_node(scene_node),
  m_physics_world_callback(std::make_unique<PhysicsWorldCallback>(command_queue)),
  m_b2_world(std::make_unique<b2World>(b2Vec2(gravity.x, gravity.y)))
{
  m_b2_world->SetContactListener(m_physics_world_callback.get());
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

const std::list<PhysicsBody*>& PhysicsWorld::getPhysicsBodies() const
{
  return m_physics_bodies;
}

const std::list<PhysicsJoint*>& PhysicsWorld::getPhysicsJoints() const
{
  return m_physics_joints;
}

void PhysicsWorld::attachPhysicsBody(PhysicsBody* physics_body)
{
  m_physics_bodies.push_back(physics_body);
}

void PhysicsWorld::detachPhysicsBody(PhysicsBody* physics_body)
{
  auto found = std::find(m_physics_bodies.begin(), m_physics_bodies.end(), physics_body);
  if (found != m_physics_bodies.end())
    m_physics_bodies.erase(found);
}

void PhysicsWorld::attachPhysicsJoint(PhysicsJoint* physics_joint)
{
  m_physics_joints.push_back(physics_joint);
}

void PhysicsWorld::detachPhysicsJoint(PhysicsJoint* physics_joint)
{
  auto found = std::find(m_physics_joints.begin(), m_physics_joints.end(), physics_joint);
  if (found != m_physics_joints.end())
    m_physics_joints.erase(found);
}

b2Body* PhysicsWorld::createInternalBody(const b2BodyDef* b2_body_def)
{
  return m_b2_world->CreateBody(b2_body_def);
}

void PhysicsWorld::destroyInternalBody(b2Body* b2_body)
{
  m_b2_world->DestroyBody(b2_body);
}

b2Joint* PhysicsWorld::createInternalJoint(const b2JointDef* b2_joint_def)
{
  return m_b2_world->CreateJoint(b2_joint_def);
}

void PhysicsWorld::destroyInternalJoint(b2Joint* b2_joint)
{
  return m_b2_world->DestroyJoint(b2_joint);
}

void PhysicsWorld::beforeSimulation()
{
  for(auto nodeIter = m_scene_node.begin(); nodeIter != m_scene_node.end(); ++nodeIter)
  {
    auto physics_body = nodeIter->getPhysicsBody();
    if(physics_body && physics_body->getPhysicsWorld() == this)
      physics_body->beforeSimulation();
  }
}

void PhysicsWorld::afterSimulation()
{
  for(auto nodeIter = m_scene_node.begin(); nodeIter != m_scene_node.end(); ++nodeIter)
  {
    auto physics_body = nodeIter->getPhysicsBody();
    if(physics_body && physics_body->getPhysicsWorld() == this)
      physics_body->afterSimulation();
  }
}

} // namespace egnim::physics
