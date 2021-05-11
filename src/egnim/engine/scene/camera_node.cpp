/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/View.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <cmath>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/camera_node.h>
#include <egnim/engine/scene/scene_visitor.h>
#include <egnim/engine/scene/scene_node.h>
#include <egnim/engine/core/context.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene {

CameraNode::CameraNode() :
  m_size(0, 0),
  m_viewport(0, 0, 0, 0),
  m_view_flag(CameraFlag::DEFAULT),
  m_zoom_factor(1.f),
  m_enabled(false)
{

}

CameraNode::~CameraNode() = default;

void CameraNode::setSize(float width, float height)
{
  m_size.x = width;
  m_size.y = height;
}

void CameraNode::setSize(const sf::Vector2f& size)
{
  m_size = size;
}

const sf::Vector2f& CameraNode::getSize() const
{
  return m_size;
}

void CameraNode::setViewport(const sf::FloatRect& viewport)
{
  m_viewport = viewport;
}

const sf::FloatRect& CameraNode::getViewport() const
{
  return m_viewport;
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

void CameraNode::setEnabled(bool enabled)
{
  m_enabled = enabled;
}

bool CameraNode::isEnabled() const
{
  return m_enabled;
}

void CameraNode::accept(SceneVisitor& visitor)
{
  visitor.visitCameraNode(*this);
}

std::unique_ptr<Node> CameraNode::clone() const
{
  auto clone_node = std::make_unique<CameraNode>();
  Node::initializeClone(*clone_node);

  clone_node->m_size = m_size;
  clone_node->m_viewport = m_viewport;
  clone_node->m_view_flag = m_view_flag;
  clone_node->m_enabled = m_enabled;
  clone_node->m_zoom_factor = m_zoom_factor;

  return clone_node;
}

} // namespace egnim::scene