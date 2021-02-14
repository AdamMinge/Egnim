/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderTarget.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/camera.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core {

std::map<sf::RenderTarget*, Camera*> Camera::s_active_camera_per_target;

Camera::Camera(sf::RenderTarget& render_target) :
  m_render_target(render_target),
  m_view_flag(CameraFlag::DEFAULT),
  m_zoom_factor(1.f)
{

}

Camera::~Camera()
{
  std::for_each(s_active_camera_per_target.begin(), s_active_camera_per_target.end(), [this](auto& camera_per_target){
    if(camera_per_target.second == this)
      camera_per_target.second = nullptr;
  });
}

void Camera::move(float offset_x, float offset_y)
{
  m_view.move(offset_x, offset_y);
}

void Camera::move(const sf::Vector2f& offset)
{
  m_view.move(offset);
}

void Camera::setCenter(float x, float y)
{
  m_view.setCenter(x, y);
}

void Camera::setCenter(const sf::Vector2f& center)
{
  m_view.setCenter(center);
}

const sf::Vector2f& Camera::getCenter() const
{
  return m_view.getCenter();
}

void Camera::setSize(float width, float height)
{
  m_view.setSize(width, height);
}

void Camera::setSize(const sf::Vector2f& size)
{
  m_view.setSize(size);
}

const sf::Vector2f& Camera::getSize() const
{
  return m_view.getSize();
}

void Camera::rotate(float angle)
{
  m_view.rotate(angle);
}

void Camera::setRotation(float angle)
{
  m_view.setRotation(angle);
}

float Camera::getRotation() const
{
  return m_view.getRotation();
}

void Camera::setViewport(const sf::FloatRect& viewport)
{
  m_view.setViewport(viewport);
}

const sf::FloatRect& Camera::getViewport() const
{
  return m_view.getViewport();
}

void Camera::setZoom(float factor)
{
  m_zoom_factor = factor;
  m_view.zoom(factor);
}

float Camera::getZoom() const
{
  return m_zoom_factor;
}

void Camera::setViewFlag(size_t flag)
{
  m_view_flag = flag;
}

size_t Camera::getViewFlag() const
{
  return m_view_flag;
}

void Camera::setActive(bool active)
{
  m_render_target.setView(m_view);
  s_active_camera_per_target[std::addressof(m_render_target)] = active ? this : nullptr;
}

bool Camera::isActive() const
{
  return std::addressof(m_render_target.getView()) == std::addressof(m_view);
}

const Camera* Camera::getActiveCamera(sf::RenderTarget& render_target)
{
  if(s_active_camera_per_target.contains(std::addressof(render_target)))
    return s_active_camera_per_target.at(std::addressof(render_target));
  else
    return nullptr;
}

} // namespace egnim::core