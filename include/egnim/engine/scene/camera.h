#ifndef CAMERA_H
#define CAMERA_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <map>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{

  class Camera
  {
  public:
    enum CameraFlag
    {
      DEFAULT = 1,
      CAMERA_1 = 1 << 1,
      CAMERA_2 = 1 << 2,
      CAMERA_3 = 1 << 3,
      CAMERA_4 = 1 << 4,
      CAMERA_5 = 1 << 5,
      CAMERA_6 = 1 << 6,
      CAMERA_7 = 1 << 7,
      CAMERA_CUSTOM = 1 << 8
    };

  public:
    explicit Camera(sf::RenderTarget& render_target);
    ~Camera();

    void move(float offset_x, float offset_y);
    void move(const sf::Vector2f& offset);

    void setCenter(float x, float y);
    void setCenter(const sf::Vector2f& center);
    const sf::Vector2f& getCenter() const;

    void setSize(float width, float height);
    void setSize(const sf::Vector2f& size);
    const sf::Vector2f& getSize() const;

    void rotate(float angle);
    void setRotation(float angle);
    float getRotation() const;

    void setViewport(const sf::FloatRect& viewport);
    const sf::FloatRect& getViewport() const;

    void setZoom(float factor);
    float getZoom() const;

    void setViewFlag(size_t flag);
    size_t getViewFlag() const;

    void setActive(bool active = true);
    bool isActive() const;

  public:
    static const Camera* getActiveCamera(sf::RenderTarget& render_target);

  private:
    sf::RenderTarget& m_render_target;
    sf::View m_view;
    size_t m_view_flag;
    float m_zoom_factor;

  private:
    static std::map<sf::RenderTarget*, Camera*> s_active_camera_per_target;
  };

} // namespace egnim::scene

#endif //CAMERA_H
