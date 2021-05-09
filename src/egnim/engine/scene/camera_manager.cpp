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

CameraNode* CameraManager::getActiveCameraNode()
{
  return m_active_camera;
}

const CameraNode* CameraManager::getActiveCameraNode() const
{
  return m_active_camera;
}

std::list<CameraNode*> CameraManager::getCameraNodes()
{
  auto cameras = std::list<CameraNode*>{};
  std::for_each(m_scene_node.begin(), m_scene_node.end(), [&cameras](auto&& node){
    if(auto camera_node = dynamic_cast<CameraNode*>(std::addressof(node)); camera_node && camera_node->isEnabled())
      cameras.push_back(camera_node);
  });

  return cameras;
}

std::list<const CameraNode*> CameraManager::getCameraNodes() const
{
  auto cameras = std::list<const CameraNode*>{};
  std::for_each(m_scene_node.begin(), m_scene_node.end(), [&cameras](auto&& node){
    if(auto camera_node = dynamic_cast<CameraNode*>(std::addressof(node)); camera_node && camera_node->isEnabled())
      cameras.push_back(camera_node);
  });

  return cameras;
}

CameraNode* CameraManager::getCameraNode(const sf::Vector2i& point)
{
  auto& target = m_scene_node.getContext().getRenderWindow();
  auto cameras = getCameraNodes();

  auto found = std::find_if(cameras.begin(), cameras.end(), [&target, &point](auto&& camera_node){
    auto target_size = target.getSize();
    auto camera_viewport = camera_node->getViewport();
    auto camera_rect = sf::Rect<unsigned>(target_size.x * camera_viewport.left,
                                          target_size.y * camera_viewport.top,
                                          target_size.x * camera_viewport.width,
                                          target_size.y * camera_viewport.height);

    return camera_rect.contains(point.x, point.y);
  });

  return found != cameras.end() ? *found : nullptr;
}

const CameraNode* CameraManager::getCameraNode(const sf::Vector2i& point) const
{
  auto& target = m_scene_node.getContext().getRenderWindow();
  auto cameras = getCameraNodes();

  auto found = std::find_if(cameras.begin(), cameras.end(), [&target, &point](auto&& camera_node){
    auto target_size = target.getSize();
    auto camera_viewport = camera_node->getViewport();
    auto camera_rect = sf::Rect<unsigned>(target_size.x * camera_viewport.left,
                                          target_size.y * camera_viewport.top,
                                          target_size.x * camera_viewport.width,
                                          target_size.y * camera_viewport.height);

    return camera_rect.contains(point.x, point.y);
  });

  return found != cameras.end() ? *found : nullptr;
}

sf::Vector2f CameraManager::mapPixelToCoords(const sf::Vector2i& point, CameraNode* camera_node) const
{
  auto& target = m_scene_node.getContext().getRenderWindow();

  if(camera_node) return target.mapPixelToCoords(point, createView(*camera_node));
  else            return target.mapPixelToCoords(point);
}

sf::Vector2i CameraManager::mapCoordsToPixel(const sf::Vector2f& point, CameraNode* camera_node) const
{
  auto& target = m_scene_node.getContext().getRenderWindow();

  if(camera_node) return target.mapCoordsToPixel(point, createView(*camera_node));
  else            return target.mapCoordsToPixel(point);
}

bool CameraManager::visitCameras(const std::function<void(CameraNode* camera_node)>& action)
{
  auto& target = m_scene_node.getContext().getRenderWindow();
  auto cameras = getCameraNodes();

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
    camera_view = createView(*camera_node);
  }

  m_active_camera = camera_node;
  target.setView(camera_view);
}

sf::View CameraManager::createView(const CameraNode& camera_node)
{
  auto camera_view = sf::View();
  camera_view.setViewport(camera_node.getViewport());
  camera_view.setRotation(camera_node.getWorldRotation());
  camera_view.setCenter(camera_node.getWorldPosition());
  camera_view.setSize(camera_node.getSize());
  camera_view.zoom(camera_node.getZoom());
  return camera_view;
}

} // namespace egnim::scene
