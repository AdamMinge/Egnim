#ifndef ANIMATED_SPRITE_NODE_H
#define ANIMATED_SPRITE_NODE_H

/* ----------------------------------- SFML --------------------------------- */

/* --------------------------------- Standard ------------------------------- */

/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/scene_node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

  class AnimatedSpriteNode : public SceneNode
  {
  public:
    explicit AnimatedSpriteNode();
    ~AnimatedSpriteNode() override;

  protected:
    void updateCurrent(CommandQueue& command_queue, sf::Time dt) override;
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
  };

} // namespace egnim::core

#endif //ANIMATED_SPRITE_NODE_H
