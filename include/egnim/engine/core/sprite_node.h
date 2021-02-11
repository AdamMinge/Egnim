#ifndef SPRITE_NODE_H
#define SPRITE_NODE_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/scene_node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

  class SpriteNode : public SceneNode
  {
  public:
    explicit SpriteNode(const sf::Texture& texture);
    explicit SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

    ~SpriteNode() override;

  protected:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

  private:
    sf::Sprite m_sprite;
  };

} // namespace egnim::core

#endif //SPRITE_NODE_H
