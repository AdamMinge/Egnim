/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/camera_node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene {

std::map<sf::RenderTarget*, CameraNode*> CameraNode::s_active_camera_per_target;

CameraNode::CameraNode() :
  m_render_target(nullptr),
  m_view_flag(CameraFlag::DEFAULT),
  m_zoom_factor(1.f)
{

}

CameraNode::~CameraNode()
{
  if(isActive())
    setActive(false);
}

void CameraNode::setRenderTarget(sf::RenderTarget* render_target)
{
  m_render_target = render_target;
}

sf::RenderTarget* CameraNode::getRenderTarget() const
{
  return m_render_target;
}

void CameraNode::setSize(float width, float height)
{
  m_view.setSize(width, height);
}

void CameraNode::setSize(const sf::Vector2f& size)
{
  setSize(size.x, size.y);
}

const sf::Vector2f& CameraNode::getSize() const
{
  return m_view.getSize();
}

void CameraNode::setViewport(const sf::FloatRect& viewport)
{
  m_view.setViewport(viewport);
}

const sf::FloatRect& CameraNode::getViewport() const
{
  return m_view.getViewport();
}

void CameraNode::setZoom(float factor)
{
  m_zoom_factor = factor;
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
  activeCamera(this, active);
}

bool CameraNode::isActive() const
{
  return m_render_target && CameraNode::getActiveCamera(*m_render_target) == this;
}

CameraNode* CameraNode::getActiveCamera(sf::RenderTarget& render_target)
{
  if(s_active_camera_per_target.contains(std::addressof(render_target)))
    return s_active_camera_per_target.at(std::addressof(render_target));
  else
    return nullptr;
}

void CameraNode::activeCamera(CameraNode* camera_node, bool active)
{
  assert(camera_node->getRenderTarget());

  camera_node->getRenderTarget()->setView(active ? camera_node->m_view : camera_node->getRenderTarget()->getDefaultView());
  s_active_camera_per_target[camera_node->getRenderTarget()] = active ? camera_node : nullptr;

  std::erase_if(s_active_camera_per_target, [](auto& camera_per_target){
    return camera_per_target.second == nullptr;
  });
}

void CameraNode::updateCurrent(sf::Time dt)
{
  m_view.setCenter(getPosition());
  m_view.setRotation(getRotation());
}

} // namespace egnim::scene