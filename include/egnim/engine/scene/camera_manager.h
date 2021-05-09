#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/View.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <list>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{

  class SceneNode;
  class CameraNode;

  class EGNIM_UTILITY_API CameraManager
  {
  public:
    explicit CameraManager(SceneNode& scene_node);
    ~CameraManager();

    [[nodiscard]] SceneNode& getSceneNode();
    [[nodiscard]] const SceneNode& getSceneNode() const;

    [[nodiscard]] CameraNode* getActiveCameraNode();
    [[nodiscard]] const CameraNode* getActiveCameraNode() const;

    [[nodiscard]] CameraNode* getCameraNode(const sf::Vector2i& point);
    [[nodiscard]] const CameraNode* getCameraNode(const sf::Vector2i& point) const;

    [[nodiscard]] std::list<CameraNode*> getCameraNodes();
    [[nodiscard]] std::list<const CameraNode*> getCameraNodes() const;

    [[nodiscard]] sf::Vector2f mapPixelToCoords(const sf::Vector2i& point, CameraNode* camera_node = nullptr) const;
    [[nodiscard]] sf::Vector2i mapCoordsToPixel(const sf::Vector2f& point, CameraNode* camera_node = nullptr) const;

    bool visitCameras(const std::function<void(CameraNode* camera_node)>& action);

  private:
    void activeCamera(sf::RenderTarget& target, CameraNode* camera_node);

    [[nodiscard]] static sf::View createView(const CameraNode& camera_node);

  private:
    SceneNode& m_scene_node;
    CameraNode* m_active_camera;
  };

} // namespace egnim::scene

#endif //CAMERA_MANAGER_H
