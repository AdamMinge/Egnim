/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/scene_node.h>
#include <egnim/engine/scene/scene_visitor.h>
#include <egnim/engine/scene/camera_manager.h>
#include <egnim/engine/physics/physics_world.h>
#include <egnim/engine/events/event_dispatcher.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene {

SceneNode::SceneNode(core::Context& context) :
  m_context(context),
  m_physics_world(std::make_unique<physics::PhysicsWorld>(*this, sf::Vector2f())),
  m_camera_manager(std::make_unique<CameraManager>(*this))
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

CameraManager& SceneNode::getCameraManager()
{
  return *m_camera_manager;
}

const CameraManager& SceneNode::getCameraManager() const
{
  return *m_camera_manager;
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

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  auto visitedAnyCamera = m_camera_manager->visitCameras([this, &target, &states](auto&& camera_node){
    Node::draw(target, states);
  });

  if(!visitedAnyCamera)
    Node::draw(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
  m_physics_world->debugDraw();
}

void SceneNode::updateCurrent(sf::Time dt)
{
  m_physics_world->update(1/60.f, 8, 3);
}

} // namespace egnim::scene