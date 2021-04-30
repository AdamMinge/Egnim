#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <map>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/scene/node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{

  class EGNIM_UTILITY_API CameraNode : public Node
  {
    EGNIM_CLASS(CameraNode, Node)

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
    explicit CameraNode();
    ~CameraNode() override;

    void setRenderTarget(sf::RenderTarget* render_target);
    [[nodiscard]] sf::RenderTarget* getRenderTarget() const;

    void setSize(float width, float height);
    void setSize(const sf::Vector2f& size);
    [[nodiscard]] const sf::Vector2f& getSize() const;

    void setViewport(const sf::FloatRect& viewport);
    [[nodiscard]] const sf::FloatRect& getViewport() const;

    void setZoom(float factor);
    [[nodiscard]] float getZoom() const;

    void setViewFlag(size_t flag);
    [[nodiscard]] size_t getViewFlag() const;

    void setActive(bool active = true);
    [[nodiscard]] bool isActive() const;

  public:
    static CameraNode* getActiveCamera(sf::RenderTarget& render_target);

  protected:
    void updateCurrent(sf::Time dt) override;

  private:
    static void activeCamera(CameraNode* camera_node, bool active);

  private:
    sf::RenderTarget* m_render_target;
    sf::View m_view;
    size_t m_view_flag;
    float m_zoom_factor;

  private:
    static std::map<sf::RenderTarget*, CameraNode*> s_active_camera_per_target;
  };

}
#endif //CAMERA_NODE_H
