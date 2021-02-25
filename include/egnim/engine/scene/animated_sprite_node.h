#ifndef ANIMATED_SPRITE_NODE_H
#define ANIMATED_SPRITE_NODE_H

/* --------------------------------- Standard ------------------------------- */
#include <map>
#include <string_view>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/node.h>
#include <egnim/engine/core/animated_sprite.h>
#include <egnim/engine/scene/node_factory.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{

  class AnimatedSpriteNode : public Node, public RegisteredInNodeFactory<AnimatedSpriteNode>
  {
    EGNIM_CLASS(AnimatedSpriteNode, Node)

  public:
    explicit AnimatedSpriteNode();
    ~AnimatedSpriteNode() override;

    void addAnimation(std::string_view id, core::AnimatedSprite&& animated_sprite);
    void removeAnimation(std::string_view id);

    void setCurrentAnimation(std::string_view id);
    std::string_view getCurrentAnimation();

    void accept(SceneVisitor& visitor) override;

  protected:
    void updateCurrent(core::CommandQueue& command_queue, sf::Time dt) override;
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

  private:
    std::map<std::string_view, core::AnimatedSprite> m_animated_sprites;
    std::map<std::string_view, core::AnimatedSprite>::iterator m_current_animation;
  };

} // namespace egnim::scene

#endif //ANIMATED_SPRITE_NODE_H
