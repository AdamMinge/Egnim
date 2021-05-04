/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/graphics/tile_layer_iterator.h>
#include <egnim/engine/graphics/tile_layer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics {

TileLayerIterator::TileLayerIterator(const TileLayer* tile_layer, IterationOrder iteration_order) :
  m_tile_layer(tile_layer),
  m_iteration_order(iteration_order),
  m_current_cell(nullptr)
{
  setToStart();
}

TileLayerIterator::TileLayerIterator(const TileLayer* tile_layer, const sf::Vector2u& start_point, IterationOrder iteration_order) :
  m_tile_layer(tile_layer),
  m_iteration_order(iteration_order),
  m_current_cell(nullptr)
{
  setToPoint(start_point);
}

TileLayerIterator::~TileLayerIterator() = default;

TileLayerIterator::IterationOrder TileLayerIterator::getIterationOrder() const
{
  return m_iteration_order;
}

sf::Vector2u TileLayerIterator::getCurrentPoint() const
{
  assert(m_current_cell);
  return m_current_point;
}

TileLayerIterator::reference TileLayerIterator::operator*() const
{
  assert(m_current_cell);
  return m_tile_layer->getCell(m_current_point);
}

TileLayerIterator::pointer TileLayerIterator::operator->()
{
  assert(m_current_cell);
  return m_tile_layer->findCell(m_current_point);
}

TileLayerIterator& TileLayerIterator::operator++()
{
  assert(m_current_cell);
  advance();
  return *this;
}

TileLayerIterator TileLayerIterator::operator++(int) // NOLINT(cert-dcl21-cpp)
{
  assert(m_current_cell);
  auto iter = *this;
  iter.advance();
  return iter;
}

bool TileLayerIterator::operator==(const TileLayerIterator& other) const
{
  assert(m_tile_layer == other.m_tile_layer && getIterationOrder() == other.getIterationOrder());
  return m_current_cell == other.m_current_cell;
}

bool TileLayerIterator::operator!=(const TileLayerIterator& other) const
{
  assert(m_tile_layer == other.m_tile_layer && getIterationOrder() == other.getIterationOrder());
  return m_current_cell == other.m_current_cell;
}

void TileLayerIterator::advance()
{
  auto last_point = getLastPoint();
  auto tile_layer_size = m_tile_layer->getSize();
  m_current_cell = nullptr;

  while(m_current_cell == nullptr && m_current_point != last_point)
  {
    if(m_iteration_order == IterationOrder::RightDown)
    {
      m_current_point.y = (m_current_point.x == 0) ? m_current_point.y - 1 : m_current_point.y;
      m_current_point.x = (m_current_point.x == 0) ? tile_layer_size.x - 1 : m_current_point.y - 1;
    }
    else if(m_iteration_order == IterationOrder::RightUp)
    {
      m_current_point.y = (m_current_point.x == 0) ? m_current_point.y + 1 : m_current_point.y;
      m_current_point.x = (m_current_point.x == 0) ? tile_layer_size.x - 1 : m_current_point.y - 1;
    }
    else if(m_iteration_order == IterationOrder::LeftDown)
    {
      m_current_point.y = (m_current_point.x == tile_layer_size.x - 1) ? m_current_point.y - 1 : m_current_point.y;
      m_current_point.x = (m_current_point.x == tile_layer_size.x - 1) ? 0 : m_current_point.x + 1;
    }
    else if(m_iteration_order == IterationOrder::LeftUp)
    {
      m_current_point.y = (m_current_point.x == tile_layer_size.x - 1) ? m_current_point.y + 1 : m_current_point.y;
      m_current_point.x = (m_current_point.x == tile_layer_size.x - 1) ? 0 : m_current_point.x + 1;
    }

    m_current_cell = m_tile_layer->findCell(m_current_point);
  }
}

void TileLayerIterator::setToPoint(const sf::Vector2u& point)
{
  assert(m_tile_layer->contains(point));
  m_current_point = point;
  m_current_cell = m_tile_layer->findCell(point);

  if(!m_current_cell)
    advance();
}

void TileLayerIterator::setToStart()
{
  setToPoint(getFirstPoint());
}

void TileLayerIterator::setToEnd()
{
  setToPoint(getLastPoint());
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

} // namespace egnim::graphics