/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderTarget.hpp>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/graphics/cell.h>
#include <egnim/engine/graphics/tile.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics {

Cell::Cell(const Tile* tile) :
  m_tile(tile)
{

}

Cell::~Cell() = default;

Cell::Cell(const Cell& other) = default;

Cell::Cell(Cell&& other) noexcept = default;

Cell& Cell::operator=(const Cell& other) = default;

Cell& Cell::operator=(Cell&& other) noexcept = default;

void Cell::setTile(const Tile* tile)
{
  m_tile = tile;
}

const Tile* Cell::getTile() const
{
  return m_tile;
}

const Tileset* Cell::getTileset() const
{
  return m_tile ? std::addressof(m_tile->getTileset()) : nullptr;
}

bool Cell::isEmpty() const
{
  return m_tile == nullptr;
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if(isEmpty())
    target.draw(*m_tile, states);
}

} // namespace egnim::graphics