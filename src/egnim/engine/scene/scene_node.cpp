/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/scene_node.h>
#include <egnim/engine/scene/visitor/scene_visitor.h>
#include <egnim/engine/physics/physics_world.h>
#include <egnim/engine/events/event_dispatcher.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene {

SceneNode::SceneNode(events::EventDispatcher& event_dispatcher) :
  m_physics_world(std::make_unique<physics::PhysicsWorld>(*this, sf::Vector2f())),
  m_event_dispatcher(event_dispatcher)
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

events::EventDispatcher& SceneNode::getEventDispatcher()
{
  return m_event_dispatcher;
}

const events::EventDispatcher& SceneNode::getEventDispatcher() const
{
  return m_event_dispatcher;
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