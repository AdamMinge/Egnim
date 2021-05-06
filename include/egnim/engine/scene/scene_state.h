#ifndef SCENE_STATE_H
#define SCENE_STATE_H

/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/core/state.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{

  class SceneNode;

  class EGNIM_UTILITY_API SceneState : public core::State
  {
  public:
    explicit SceneState(core::StateStack& state_stack, core::Context& context);
    ~SceneState() override;

    void draw() override;
    void update(sf::Time dt) override;

    void onActive() override;
    void onInactive() override;

    [[nodiscard]] SceneNode& getSceneNode();
    [[nodiscard]] const SceneNode& getSceneNode() const;

  private:
    std::unique_ptr<SceneNode> m_scene_node;
  };

} // namespace egnim::scene

#endif //SCENE_STATE_H
