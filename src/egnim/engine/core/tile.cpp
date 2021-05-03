/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderTarget.hpp>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/core/tile.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core {


Tile::Tile(Tileset& tileset, sf::Sprite sprite, unsigned id) :
  m_tileset(tileset),
  m_sprite(std::move(sprite)),
  m_id(id)
{

}

Tile::~Tile() = default;

const Tileset& Tile::getTileset() const
{
  return m_tileset;
}

unsigned Tile::getId() const
{
  return m_id;
}

sf::Vector2u Tile::getSize() const
{
  auto rect = m_sprite.getTextureRect();
  return sf::Vector2u(rect.width, rect.height);
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_sprite, states);
}

} // namespace egnim::core