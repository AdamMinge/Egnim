/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/scene_node.h>
#include <egnim/engine/scene/scene_visitor.h>
#include <egnim/engine/physics/physics_world.h>
#include <egnim/engine/events/event_dispatcher.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene {

SceneNode::SceneNode(core::Context& context) :
  m_physics_world(std::make_unique<physics::PhysicsWorld>(*this, sf::Vector2f())),
  m_context(context)
{

}

SceneNode::~SceneNode() = default;

physics::PhysicsWorld& SceneNode::getPhysicsWorld()
{
  return *m_physics_world;
}

const physics::PhysicsWorld& SceneNode::getPhysicsWorld() const
{
  return *m_physics_world;
}

core::Context& SceneNode::getContext()
{
  return m_context;
}

const core::Context& SceneNode::getContext() const
{
  return m_context;
}

void SceneNode::accept(SceneVisitor& visitor)
{
  visitor.visitSceneNode(*this);
}

void SceneNode::updateCurrent(sf::Time dt)
{
  m_physics_world->update(1/60.f, 8, 3);
}

} // namespace egnim::scene