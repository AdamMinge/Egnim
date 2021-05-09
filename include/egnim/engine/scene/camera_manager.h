#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

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

    [[nodiscard]] CameraNode* getActiveCamera();
    [[nodiscard]] const CameraNode* getActiveCamera() const;

    bool visitCameras(const std::function<void(CameraNode* camera_node)>& action);

  private:
    void activeCamera(sf::RenderTarget& target, CameraNode* camera_node);

  private:
    SceneNode& m_scene_node;
    CameraNode* m_active_camera;
  };

} // namespace egnim::scene

#endif //CAMERA_MANAGER_H
