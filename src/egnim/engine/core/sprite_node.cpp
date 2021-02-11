/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderTarget.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/sprite_node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core {

SpriteNode::SpriteNode(const sf::Texture &texture) :
  m_sprite(texture)
{

}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect) :
  m_sprite(texture, rect)
{

}


SpriteNode::~SpriteNode() = default;

void SpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(m_sprite, states);
}


} // namespace egnim::core