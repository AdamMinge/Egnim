/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/View.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <cmath>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/camera_node.h>
#include <egnim/engine/scene/visitor/scene_visitor.h>
#include <egnim/engine/scene/scene_node.h>
#include <egnim/engine/core/context.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene {

/* --------------------------------- CameraNode ----------------------------- */

CameraNode::CameraNode() :
  m_size(0, 0),
  m_viewport(0, 0, 0, 0),
  m_view_flag(CameraFlag::DEFAULT),
  m_zoom_factor(1.f)
{

}

CameraNode::~CameraNode()
{
  if(isActive())
    setActive(false);
}

void CameraNode::setSize(float width, float height)
{
  m_size.x = width;
  m_size.y = height;
  CameraManager::getInstance().update(*this);
}

void CameraNode::setSize(const sf::Vector2f& size)
{
  m_size = size;
  CameraManager::getInstance().update(*this);
}

const sf::Vector2f& CameraNode::getSize() const
{
  return m_size;
}

void CameraNode::setViewport(const sf::FloatRect& viewport)
{
  m_viewport = viewport;
  CameraManager::getInstance().update(*this);
}

const sf::FloatRect& CameraNode::getViewport() const
{
  return m_viewport;
}

void CameraNode::setZoom(float factor)
{
  m_zoom_factor = factor;
  CameraManager::getInstance().update(*this);
}

float CameraNode::getZoom() const
{
  return m_zoom_factor;
}

void CameraNode::setViewFlag(size_t flag)
{
  m_view_flag = flag;
}

size_t CameraNode::getViewFlag() const
{
  return m_view_flag;
}

void CameraNode::setActive(bool active)
{
  if(active)  CameraManager::getInstance().activeCamera(*this);
  else        CameraManager::getInstance().deactivateCamera(*this);
}

bool CameraNode::isActive() const
{
  return CameraManager::getInstance().isActiveCamera(*this);
}

void CameraNode::accept(SceneVisitor& visitor)
{
  visitor.visitCameraNode(*this);
}

/* -------------------------------- CameraManager --------------------------- */

std::unique_ptr<CameraManager> CameraManager::s_instance = nullptr;

CameraManager::CameraManager() = default;

CameraManager::~CameraManager() = default;

CameraManager& CameraManager::getInstance()
{
  if(!s_instance)
    s_instance = std::unique_ptr<CameraManager>(new CameraManager);
  return *s_instance;
}

CameraNode* CameraManager::getActiveCamera(sf::RenderTarget& render_target)
{
  if(!m_render_target_to_camera_node.contains(std::addressof(render_target)))
    return nullptr;

  return m_render_target_to_camera_node.at(std::addressof(render_target));
}

const CameraNode* CameraManager::getActiveCamera(sf::RenderTarget& render_target) const
{
  if(!m_render_target_to_camera_node.contains(std::addressof(render_target)))
    return nullptr;

  return m_render_target_to_camera_node.at(std::addressof(render_target));
}

void CameraManager::activeCamera(CameraNode& camera_node)
{
  assert(camera_node.getScene());
  auto& render_target = camera_node.getScene()->getContext().getRenderWindow();
  m_render_target_to_camera_node[std::addressof(render_target)] = std::addressof(camera_node);
  update(camera_node);
}

void CameraManager::deactivateCamera(CameraNode& camera_node)
{
  auto found = std::find_if(m_render_target_to_camera_node.begin(), m_render_target_to_camera_node.end(),
                [&camera_node](auto&& target_to_camera){
    return target_to_camera.second == std::addressof(camera_node);
  });

  if(found != m_render_target_to_camera_node.end())
  {
    auto render_target = found->first;
    render_target->setView(render_target->getDefaultView());
    m_render_target_to_camera_node.erase(found);
  }
}

void CameraManager::update(CameraNode& camera_node)
{
  assert(camera_node.getScene());
  if(isActiveCamera(camera_node))
  {
    auto& render_target = camera_node.getScene()->getContext().getRenderWindow();
    auto view = sf::View(camera_node.getViewport());
    view.zoom(camera_node.getZoom());
    view.setCenter(camera_node.getWorldPosition());
    view.setRotation(camera_node.getWorldRotation());
    view.setSize(camera_node.getSize());

    render_target.setView(view);
  }
}

bool CameraManager::isActiveCamera(const CameraNode& camera_node) const
{
  auto found = std::find_if(m_render_target_to_camera_node.begin(), m_render_target_to_camera_node.end(),
               [&camera_node](auto&& target_to_camera){
    return target_to_camera.second == std::addressof(camera_node);
  });

  return found != m_render_target_to_camera_node.end();
}

} // namespace egnim::scene