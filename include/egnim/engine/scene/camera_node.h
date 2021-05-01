#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H

/* --------------------------------- Standard ------------------------------- */
#include <map>
#include <memory>
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
      DEFAULT = 1 << 0,
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

    void accept(SceneVisitor& visitor) override;

  private:
    sf::Vector2f m_size;
    sf::FloatRect m_viewport;
    size_t m_view_flag;
    float m_zoom_factor;
  };

  class EGNIM_UTILITY_API CameraManager
  {
    friend CameraNode;

  public:
    ~CameraManager();

    [[nodiscard]] static CameraManager& getInstance();

    [[nodiscard]] CameraNode* getActiveCamera(sf::RenderTarget& render_target);
    [[nodiscard]] const CameraNode* getActiveCamera(sf::RenderTarget& render_target) const;

    void setDefaultCamera(sf::RenderTarget& render_target);
    [[nodiscard]] bool hasDefaultCamera(sf::RenderTarget& render_target) const;

  private:
    explicit CameraManager();

    void activeCamera(CameraNode& camera_node);
    void deactivateCamera(CameraNode& camera_node);

    void update(CameraNode& camera_node);

    [[nodiscard]] bool isActiveCamera(const CameraNode& camera_node) const;

  private:
    static std::unique_ptr<CameraManager> s_instance;
    std::map<sf::RenderTarget*, CameraNode*> m_render_target_to_camera_node;
  };

}
#endif //CAMERA_NODE_H
