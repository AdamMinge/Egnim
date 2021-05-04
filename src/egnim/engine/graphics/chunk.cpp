/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderTarget.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/graphics/chunk.h>
#include <egnim/engine/graphics/tile.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics {

Chunk::Chunk(const sf::Vector2u& size) :
  m_grid(size.x * size.y),
  m_size(size)
{

}

Chunk::~Chunk() = default;

Chunk::Chunk(const Chunk& other) = default;

Chunk::Chunk(Chunk&& other) noexcept = default;

Chunk& Chunk::operator=(const Chunk& other) = default;

Chunk& Chunk::operator=(Chunk&& other) noexcept = default;

void Chunk::setCell(const sf::Vector2u& point, const Cell& cell)
{
  assert(contains(point));
  auto index = (point.y * m_size.x) + point.x;
  m_grid[index] = cell;
}

const Cell& Chunk::getCell(const sf::Vector2u& point) const
{
  auto found_cell = findCell(point);
  assert(found_cell);

  return *found_cell;
}

const Cell* Chunk::findCell(const sf::Vector2u& point) const
{
  auto index = (point.y * m_size.x) + point.x;
  return std::addressof(m_grid[index]);
}

bool Chunk::contains(const sf::Vector2u& point) const
{
  auto index = (point.y * m_size.x) + point.x;
  return index >= 0 && index < m_grid.size();
}

bool Chunk::isEmpty() const
{
  return std::all_of(m_grid.begin(), m_grid.end(), [](auto& cell) { return cell.isEmpty(); });
}

const sf::Vector2u& Chunk::getSize() const
{
  return m_size;
}

} // namespace egnim::graphics