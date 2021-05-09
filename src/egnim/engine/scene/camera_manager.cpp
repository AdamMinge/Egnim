/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderTarget.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <list>
#include <cassert>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/context.h>
#include <egnim/engine/scene/camera_manager.h>
#include <egnim/engine/scene/camera_node.h>
#include <egnim/engine/scene/scene_node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene {

CameraManager::CameraManager(SceneNode& scene_node) :
  m_scene_node(scene_node),
  m_active_camera(nullptr)
{

}

CameraManager::~CameraManager() = default;

SceneNode& CameraManager::getSceneNode()
{
  return m_scene_node;
}

const SceneNode& CameraManager::getSceneNode() const
{
  return m_scene_node;
}

CameraNode* CameraManager::getActiveCamera()
{
  return m_active_camera;
}

const CameraNode* CameraManager::getActiveCamera() const
{
  return m_active_camera;
}

bool CameraManager::visitCameras(const std::function<void(CameraNode* camera_node)>& action)
{
  auto cameras = std::list<CameraNode*>{};
  auto& target = m_scene_node.getContext().getRenderWindow();

  std::for_each(m_scene_node.begin(), m_scene_node.end(), [&cameras](auto&& node){
    if(auto camera_node = dynamic_cast<CameraNode*>(std::addressof(node)); camera_node && camera_node->isEnabled())
      cameras.push_back(camera_node);
  });

  std::for_each(cameras.begin(), cameras.end(), [this, &target, &action](auto&& camera_node){
    activeCamera(target, camera_node);
    action(camera_node);
  });

  activeCamera(target, nullptr);

  return !cameras.empty();
}

void CameraManager::activeCamera(sf::RenderTarget& target, CameraNode* camera_node)
{
  auto camera_view = target.getDefaultView();
  if(camera_node)
  {
    assert(camera_node->isEnabled());

    camera_view = sf::View();
    camera_view.setViewport(camera_node->getViewport());
    camera_view.setRotation(camera_node->getWorldRotation());
    camera_view.setCenter(camera_node->getWorldPosition());
    camera_view.setSize(camera_node->getSize());
    camera_view.zoom(camera_node->getZoom());
  }

  m_active_camera = camera_node;
  target.setView(camera_view);
}

} // namespace egnim::scene
