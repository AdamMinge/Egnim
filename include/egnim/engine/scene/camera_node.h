#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H

/* --------------------------------- Standard ------------------------------- */
#include <map>
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/scene/node.h>
#include <egnim/engine/scene/node_factory.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{

  class EGNIM_UTILITY_API CameraNode : public Node, public RegisteredInNodeFactory<CameraNode>
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

    void setEnabled(bool enabled);
    [[nodiscard]] bool isEnabled() const;

    void accept(SceneVisitor& visitor) override;

  private:
    sf::Vector2f m_size;
    sf::FloatRect m_viewport;
    size_t m_view_flag;
    float m_zoom_factor;
    bool m_enabled;
  };

}
#endif //CAMERA_NODE_H
