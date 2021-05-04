/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Sprite.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/graphics/tileset.h>
#include <egnim/engine/graphics/tile.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics {

Tileset::Tileset(sf::Texture& texture, const sf::Vector2u& tile_size, unsigned spacing, unsigned margin) :
  m_texture(texture),
  m_tile_size(tile_size),
  m_spacing(spacing),
  m_margin(margin),
  m_column_count(0),
  m_row_count(0)
{
  init();
}

Tileset::~Tileset() = default;

void Tileset::setTileSize(const sf::Vector2u& tile_size)
{
  changeValue(m_tile_size, tile_size);
}

const sf::Vector2u& Tileset::getTileSize() const
{
  return m_tile_size;
}

void Tileset::setSpacing(unsigned spacing)
{
  changeValue(m_spacing, spacing);
}

unsigned Tileset::getSpacing() const
{
  return m_spacing;
}

void Tileset::setMargin(unsigned margin)
{
  changeValue(m_margin, margin);
}

unsigned Tileset::getMargin() const
{
  return m_margin;
}

const Tile& Tileset::getTile(unsigned id) const
{
  assert(m_tiles.contains(id));
  return *m_tiles.at(id);
}

unsigned Tileset::getTileCount() const
{
  return m_tiles.size();
}

unsigned Tileset::getColumnCount() const
{
  return m_column_count;
}

unsigned Tileset::getRowCount() const
{
  return m_row_count;
}

bool Tileset::contains(const Tile& tile) const
{
  return std::addressof(tile.getTileset()) == this;
}

void Tileset::init()
{
  assert(m_tile_size.x > 0 && m_tile_size.y > 0);
  m_tiles.clear();

  auto tileNum = 0u;
  for(auto y = m_margin; y <= m_texture.getSize().y - m_tile_size.y; y += m_tile_size.y + m_spacing)
  {
    for(auto x = m_margin; x <= m_texture.getSize().x - m_tile_size.x; x += m_tile_size.x + m_spacing)
    {
      auto tile_rect = sf::IntRect(static_cast<int>(x), static_cast<int>(y),
                                   static_cast<int>(m_tile_size.x), static_cast<int>(m_tile_size.y));
      auto sprite = sf::Sprite(m_texture, tile_rect);
      m_tiles.insert(std::make_pair(tileNum, std::unique_ptr<Tile>(new Tile(*this, sprite, tileNum))));
    }
  }

  m_column_count = (m_texture.getSize().x - m_margin + m_spacing) / (m_tile_size.x + m_spacing);
  m_row_count = (m_texture.getSize().y - m_margin + m_spacing) / (m_tile_size.y + m_spacing);

  assert(m_column_count > 0);
  assert(m_row_count > 0);
}

} // namespace egnim::graphics