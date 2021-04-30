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
  namespace events { class EventDispatcher; }
}

namespace egnim::scene
{

  class EGNIM_UTILITY_API SceneNode : public Node
  {
    EGNIM_CLASS(SceneNode, Node)

  public:
    explicit SceneNode(events::EventDispatcher& event_dispatcher);
    ~SceneNode() override;

    physics::PhysicsWorld& getPhysicsWorld();
    const physics::PhysicsWorld& getPhysicsWorld() const;

    events::EventDispatcher& getEventDispatcher();
    const events::EventDispatcher& getEventDispatcher() const;

    void accept(SceneVisitor& visitor) override;

  protected:
    void updateCurrent(sf::Time dt) override;

  private:
    std::unique_ptr<physics::PhysicsWorld> m_physics_world;
    events::EventDispatcher& m_event_dispatcher;
  };

} // namespace egnim::scene

#endif //SCENE_NODE_H
