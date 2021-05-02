/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/core/chunk.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core {

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

const Cell& Chunk::getCell(const sf::Vector2u& point)
{
  auto found_cell = findCell(point);
  assert(found_cell);

  return *found_cell;
}

const Cell* Chunk::findCell(const sf::Vector2u& point)
{
  auto index = (point.y * m_size.x) + point.x;
  return std::addressof(m_grid[index]);
}

bool Chunk::contains(const sf::Vector2u& point)
{
  auto index = (point.y * m_size.x) + point.x;
  return index >= 0 && index < m_grid.size();
}

bool Chunk::isEmpty() const
{
  return std::all_of(begin(), end(), [](auto& cell) { return cell.isEmpty(); });
}

std::vector<Cell>::iterator Chunk::begin()
{
  return m_grid.begin();
}

std::vector<Cell>::const_iterator Chunk::begin() const
{
  return m_grid.cbegin();
}

std::vector<Cell>::iterator Chunk::end()
{
  return m_grid.end();
}

std::vector<Cell>::const_iterator Chunk::end() const
{
  return m_grid.cend();
}

void Chunk::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

} // namespace egnim::core