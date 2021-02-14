#ifndef ANIMATED_SPRITE_NODE_H
#define ANIMATED_SPRITE_NODE_H

/* --------------------------------- Standard ------------------------------- */
#include <map>
#include <string_view>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/node.h>
#include <egnim/engine/core/animated_sprite.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

  class AnimatedSpriteNode : public Node
  {
  public:
    explicit AnimatedSpriteNode();
    ~AnimatedSpriteNode() override;

    void addAnimation(std::string_view id, AnimatedSprite&& animated_sprite);
    void removeAnimation(std::string_view id);

    void setCurrentAnimation(std::string_view id);
    std::string_view getCurrentAnimation();

  protected:
    void updateCurrent(CommandQueue& command_queue, sf::Time dt) override;
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

  private:
    std::map<std::string_view, AnimatedSprite> m_animated_sprites;
    std::map<std::string_view, AnimatedSprite>::iterator m_current_animation;
  };

} // namespace egnim::core

#endif //ANIMATED_SPRITE_NODE_H
