/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/core/tile_layer_iterator.h>
#include <egnim/engine/core/tile_layer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core {

/* ---------------------------- TileLayerIterator --------------------------- */

TileLayerIterator::TileLayerIterator(TileLayer& tile_layer, IterationOrder iteration_order, bool end) :
  m_tile_layer(std::addressof(tile_layer)),
  m_iteration_order(iteration_order),
  m_end(end)
{
  m_current_point = getFirstPoint();
}

TileLayerIterator::~TileLayerIterator() = default;

TileLayerIterator::IterationOrder TileLayerIterator::getIterationOrder() const
{
  return m_iteration_order;
}

sf::Vector2u TileLayerIterator::getCurrentPoint() const
{
  return m_current_point;
}

TileLayerIterator::reference TileLayerIterator::operator*() const
{
  assert(m_tile_layer->contains(m_current_point) && !m_end);
  return m_tile_layer->getCell(m_current_point);
}

TileLayerIterator::pointer TileLayerIterator::operator->()
{
  assert(m_tile_layer->contains(m_current_point) && !m_end);
  return m_tile_layer->findCell(m_current_point);
}

TileLayerIterator& TileLayerIterator::operator++()
{
  advance(*this);
  return *this;
}

TileLayerIterator TileLayerIterator::operator++(int) // NOLINT(cert-dcl21-cpp)
{
  auto iter = *this;
  advance(iter);
  return iter;
}

bool TileLayerIterator::operator==(const TileLayerIterator& other) const
{
  assert(m_tile_layer == other.m_tile_layer && getIterationOrder() == other.getIterationOrder());
  return getCurrentPoint() == other.getCurrentPoint() && m_end == other.m_end;
}

bool TileLayerIterator::operator!=(const TileLayerIterator& other) const
{
  assert(m_tile_layer == other.m_tile_layer && getIterationOrder() == other.getIterationOrder());
  return getCurrentPoint() != other.getCurrentPoint() || m_end != other.m_end;;
}

void TileLayerIterator::advance(TileLayerIterator& iter)
{
  if(getCurrentPoint() == getLastPoint())
  {
    assert(!m_end);
    m_end = true;
    return;
  }

  if(m_iteration_order == IterationOrder::RightDown)
  {
    m_current_point.y = (m_current_point.x == 0) ? m_current_point.y - 1 : m_current_point.y;
    m_current_point.x = (m_current_point.x == 0) ? m_tile_layer->getSize().x - 1 : m_current_point.y - 1;
  }
  else if(m_iteration_order == IterationOrder::RightUp)
  {
    m_current_point.y = (m_current_point.x == 0) ? m_current_point.y + 1 : m_current_point.y;
    m_current_point.x = (m_current_point.x == 0) ? m_tile_layer->getSize().x - 1 : m_current_point.y - 1;
  }
  else if(m_iteration_order == IterationOrder::LeftDown)
  {
    m_current_point.y = (m_current_point.x == m_tile_layer->getSize().x - 1) ? m_current_point.y - 1 : m_current_point.y;
    m_current_point.x = (m_current_point.x == m_tile_layer->getSize().x - 1) ? 0 : m_current_point.x + 1;
  }
  else if(m_iteration_order == IterationOrder::LeftUp)
  {
    m_current_point.y = (m_current_point.x == m_tile_layer->getSize().x - 1) ? m_current_point.y + 1 : m_current_point.y;
    m_current_point.x = (m_current_point.x == m_tile_layer->getSize().x - 1) ? 0 : m_current_point.x + 1;
  }
}

sf::Vector2u TileLayerIterator::getFirstPoint() const
{
  if(m_iteration_order == IterationOrder::RightDown)
    return sf::Vector2u(m_tile_layer->getSize().x  - 1, m_tile_layer->getSize().y - 1);

  if(m_iteration_order == IterationOrder::RightUp)
    return sf::Vector2u(m_tile_layer->getSize().x  - 1, 0u);

  if(m_iteration_order == IterationOrder::LeftDown)
    return sf::Vector2u(0u, m_tile_layer->getSize().y  - 1);

  return sf::Vector2u(0u, 0u);
}

sf::Vector2u TileLayerIterator::getLastPoint() const
{
  if(m_iteration_order == IterationOrder::RightDown)
    return sf::Vector2u(0u, 0u);

  if(m_iteration_order == IterationOrder::RightUp)
    return sf::Vector2u(0u, m_tile_layer->getSize().y  - 1);

  if(m_iteration_order == IterationOrder::LeftDown)
    return sf::Vector2u(m_tile_layer->getSize().x  - 1, 0u);

  return sf::Vector2u(m_tile_layer->getSize().x  - 1, m_tile_layer->getSize().y  - 1);
}

} // namespace egnim::core