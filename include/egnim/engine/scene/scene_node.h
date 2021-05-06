#ifndef SCENE_NODE_H
#define SCENE_NODE_H

/* --------------------------------- Standard ------------------------------- */
#include <map>
#include <memory>
#include <string_view>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/scene/node.h>
/* -------------------------------------------------------------------------- */

namespace egnim
{
  namespace physics { class PhysicsWorld; }
  namespace core { class Context; }
}

namespace egnim::scene
{

  class EGNIM_UTILITY_API SceneNode : public Node
  {
    EGNIM_CLASS(SceneNode, Node)

  public:
    explicit SceneNode(core::Context& context);
    ~SceneNode() override;

    physics::PhysicsWorld& getPhysicsWorld();
    const physics::PhysicsWorld& getPhysicsWorld() const;

    core::Context& getContext();
    const core::Context& getContext() const;

    void accept(SceneVisitor& visitor) override;

  protected:
    void updateCurrent(sf::Time dt) override;

  private:
    core::Context& m_context;
    std::unique_ptr<physics::PhysicsWorld> m_physics_world;
  };

} // namespace egnim::scene

#endif //SCENE_NODE_H
