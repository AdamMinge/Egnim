/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderTarget.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/sprite_node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core {

SpriteNode::SpriteNode() = default;

SpriteNode::~SpriteNode() = default;

void SpriteNode::setTexture(const sf::Texture& texture)
{
  m_sprite.setTexture(texture);
}

void SpriteNode::setTextureRect(const sf::IntRect& rect)
{
  m_sprite.setTextureRect(rect);
}

const sf::Texture& SpriteNode::getTexture() const
{
  return *m_sprite.getTexture();
}

const sf::IntRect& SpriteNode::getTextureRect() const
{
  return m_sprite.getTextureRect();
}

void SpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(m_sprite, states);
}


} // namespace egnim::core