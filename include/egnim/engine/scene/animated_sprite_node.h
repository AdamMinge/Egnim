#ifndef ANIMATED_SPRITE_NODE_H
#define ANIMATED_SPRITE_NODE_H

/* --------------------------------- Standard ------------------------------- */
#include <map>
#include <string_view>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/scene/node.h>
#include <egnim/engine/graphics/animated_sprite.h>
#include <egnim/engine/scene/node_factory.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{

  class EGNIM_UTILITY_API AnimatedSpriteNode : public Node, public RegisteredInNodeFactory<AnimatedSpriteNode>
  {
    EGNIM_CLASS(AnimatedSpriteNode, Node)

  public:
    [[nodiscard]] static std::unique_ptr<AnimatedSpriteNode> create();

  public:
    ~AnimatedSpriteNode() override;

    void addAnimation(std::string_view id, graphics::AnimatedSprite&& animated_sprite);
    void removeAnimation(std::string_view id);

    void setCurrentAnimation(std::string_view id);
    std::string_view getCurrentAnimation();

    void accept(SceneVisitor& visitor) override;

  protected:
    explicit AnimatedSpriteNode();

    void updateCurrent(sf::Time dt) override;
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

  private:
    std::map<std::string_view, graphics::AnimatedSprite> m_animated_sprites;
    std::map<std::string_view, graphics::AnimatedSprite>::iterator m_current_animation;
  };

} // namespace egnim::scene

#endif //ANIMATED_SPRITE_NODE_H
