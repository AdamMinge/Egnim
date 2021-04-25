#ifndef SCENE_NODE_H
#define SCENE_NODE_H

/* --------------------------------- Standard ------------------------------- */
#include <map>
#include <memory>
#include <string_view>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/scene/node.h>
#include <egnim/engine/scene/node_factory.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics
{
  class PhysicsWorld;
}

namespace egnim::scene
{
  class Camera;

  class EGNIM_UTILITY_API SceneNode : public Node, public RegisteredInNodeFactory<SceneNode>
  {
    EGNIM_CLASS(SceneNode, Node)

  public:
    explicit SceneNode();
    ~SceneNode() override;

    void attachCamera(std::string_view id, std::unique_ptr<Camera> camera);
    std::unique_ptr<Camera> detachCamera(std::string_view id);

    Camera& getCamera(std::string_view id);
    const Camera& getCamera(std::string_view id) const;

    physics::PhysicsWorld& getPhysicsWorld();
    const physics::PhysicsWorld& getPhysicsWorld() const;

    void accept(SceneVisitor& visitor) override;

  protected:
    void updateCurrent(sf::Time dt) override;

  private:
    std::map<std::string_view, std::unique_ptr<Camera>> m_cameras;
    std::unique_ptr<physics::PhysicsWorld> m_physics_world;
  };

} // namespace egnim::scene

#endif //SCENE_NODE_H
