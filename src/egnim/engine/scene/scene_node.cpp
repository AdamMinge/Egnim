/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderTarget.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/scene_node.h>
#include <egnim/engine/scene/camera.h>
#include <egnim/engine/scene/visitor/scene_visitor.h>
#include <egnim/engine/physics/physics_world.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene {

SceneNode::SceneNode() :
  m_physics_world(std::make_unique<physics::PhysicsWorld>(*this, sf::Vector2f()))
{

}

SceneNode::~SceneNode() = default;

void SceneNode::attachCamera(std::string_view id, std::unique_ptr<Camera> camera)
{
  assert(!m_cameras.contains(id));
  m_cameras.insert(std::make_pair(id, std::move(camera)));
}

std::unique_ptr<Camera> SceneNode::detachCamera(std::string_view id)
{
  assert(m_cameras.contains(id));
  auto camera = std::move(m_cameras.at(id));
  m_cameras.erase(id);

  return camera;
}

Camera& SceneNode::getCamera(std::string_view id)
{
  assert(m_cameras.contains(id));
  return *m_cameras.at(id);
}

const Camera& SceneNode::getCamera(std::string_view id) const
{
  assert(m_cameras.contains(id));
  return *m_cameras.at(id);
}

physics::PhysicsWorld& SceneNode::getPhysicsWorld()
{
  return *m_physics_world;
}

const physics::PhysicsWorld& SceneNode::getPhysicsWorld() const
{
  return *m_physics_world;
}

void SceneNode::accept(SceneVisitor& visitor)
{
  visitor.visitSceneNode(*this);
}

} // namespace egnim::scene