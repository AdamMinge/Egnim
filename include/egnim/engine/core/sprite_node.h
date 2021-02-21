#ifndef SPRITE_NODE_H
#define SPRITE_NODE_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/node.h>
#include <egnim/engine/core/node_factory.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

  class SpriteNode : public Node, public RegisteredInNodeFactory<SpriteNode>
  {
    EGNIM_CLASS(SpriteNode, Node)

  public:
    explicit SpriteNode();
    ~SpriteNode() override;

    void setTexture(const sf::Texture& texture);
    void setTextureRect(const sf::IntRect& rect);

    const sf::Texture& getTexture() const;
    const sf::IntRect& getTextureRect() const;

  protected:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

  private:
    sf::Sprite m_sprite;
  };

} // namespace egnim::core

#endif //SPRITE_NODE_H
