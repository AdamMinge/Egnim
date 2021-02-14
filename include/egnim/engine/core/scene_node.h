#ifndef SCENE_NODE_H
#define SCENE_NODE_H

/* --------------------------------- Standard ------------------------------- */
#include <map>
#include <memory>
#include <string_view>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{
  class Camera;

  class SceneNode : public Node
  {
  public:
    explicit SceneNode();
    ~SceneNode() override;

    void attachCamera(std::string_view id, std::unique_ptr<Camera> camera);
    std::unique_ptr<Camera> detachCamera(std::string_view id);

    Camera& getCamera(std::string_view id);
    const Camera& getCamera(std::string_view id) const;

  private:
    std::map<std::string_view, std::unique_ptr<Camera>> m_cameras;
  };

} // namespace egnim::core

#endif //SCENE_NODE_H
