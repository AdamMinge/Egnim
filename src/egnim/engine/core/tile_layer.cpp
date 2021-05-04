/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/core/tile_layer.h>
/* -------------------------------------------------------------------------- */

namespace sf {

bool operator<(const sf::Vector2<unsigned int>& first, const sf::Vector2<unsigned int>& second)
{
  if(first.x < second.x)
    return true;

  return first.x == second.x && first.y < second.y;
}

} // namespace sf

namespace egnim::core {

TileLayer::TileLayer(const sf::Vector2u& size, const sf::Vector2u& chunk_size) :
  Layer(Type::TileLayer),
  m_size(size),
  m_chunk_size(chunk_size)
{
  assert(m_size.x > 0 && m_size.y > 0);
}

TileLayer::~TileLayer() = default;

void TileLayer::setSize(const sf::Vector2u& size)
{
  m_size = size;
  assert(m_size.x > 0 && m_size.y > 0);
}

const sf::Vector2u& TileLayer::getSize() const
{
  return m_size;
}

const sf::Vector2u& TileLayer::getChunkSize() const
{
  return m_chunk_size;
}

sf::IntRect TileLayer::getBounds() const
{
  return m_bounds;
}

sf::IntRect TileLayer::getRect() const
{
  return sf::IntRect(0, 0, static_cast<int>(m_size.x), static_cast<int>(m_size.y));
}

bool TileLayer::contains(const sf::Vector2u& point) const
{
  return point.x < m_size.x && point.y < m_size.y;
}

const Chunk& TileLayer::getChunk(const sf::Vector2u& point) const
{
  auto chunk_coordinates = sf::Vector2u(point.x / getChunkSize().x, point.y / getChunkSize().y);
  auto chunk = findChunk(chunk_coordinates);
  assert(chunk);

  return *chunk;
}

const Chunk* TileLayer::findChunk(const sf::Vector2u& point) const
{
  auto chunk_coordinates = sf::Vector2u(point.x / getChunkSize().x, point.y / getChunkSize().y);
  auto iter = m_chunks.find(chunk_coordinates);

  return iter != m_chunks.end() ? std::addressof(iter->second) : nullptr;
}

void TileLayer::setCell(const sf::Vector2u& point, const Cell& cell)
{
  if(contains(point))
    return;

  auto found_chunk = findChunk(point);
  assert(found_chunk);

  auto chunk_coordinate = toChunkCoordinate(point);
  auto new_tileset = cell.getTileset();
  auto old_tileset = found_chunk->getCell(chunk_coordinate).getTileset();

  if(new_tileset != old_tileset)
  {
    if(old_tileset) m_used_tilesets[old_tileset] -= 1;
    if(new_tileset) m_used_tilesets[new_tileset] += 1;

    if(m_used_tilesets[old_tileset] == 0)
      m_used_tilesets.erase(old_tileset);
  }

  found_chunk->setCell(chunk_coordinate, cell);
}

const Cell& TileLayer::getCell(const sf::Vector2u& point) const
{
  auto found_cell = findCell(point);
  assert(found_cell);

  return *found_cell;
}

const Cell* TileLayer::findCell(const sf::Vector2u& point) const
{
  auto found_chunk = findChunk(point);
  return found_chunk ? found_chunk->findCell(toChunkCoordinate(point)) : nullptr;
}

bool TileLayer::isEmpty() const
{
  return std::all_of(m_chunks.begin(), m_chunks.end(), [](auto& pair) {
    return pair.second.isEmpty();
  });
}

std::list<const Tileset*> TileLayer::getUsedTilesets() const
{
  auto used_tilesets = std::list<const Tileset*>{};
  std::transform(m_used_tilesets.begin(), m_used_tilesets.end(), std::back_inserter(used_tilesets), [](auto& pair) {
    return pair.first;
  });

  return used_tilesets;
}

bool TileLayer::isUsedTileset(const Tileset& tileset) const
{
  return m_used_tilesets.contains(std::addressof(tileset));
}

bool TileLayer::canMerge(const Layer& layer) const
{
  return layer.getType() == getType();
}

bool TileLayer::merge(const sf::Vector2u& point, const Layer& layer)
{
  auto tile_layer = dynamic_cast<const TileLayer*>(std::addressof(layer));
  if(!tile_layer)
    return false;

  auto layer_area = sf::Rect<unsigned>(point, tile_layer->getSize());
  auto this_layer_area = sf::Rect<unsigned>(sf::Vector2u(), getSize());
  auto intersect_area = sf::Rect<unsigned>();

  if(this_layer_area.intersects(layer_area, intersect_area))
  {
    for(auto y = intersect_area.top; y <= intersect_area.top + intersect_area.height; ++y)
    {
      for(auto x = intersect_area.left; x <= intersect_area.left + intersect_area.width; ++x)
      {
        auto from_cell_coordinate = sf::Vector2u(x - point.x, y - point.y);
        auto to_cell_coordinate = sf::Vector2u(x, y);

        auto cell = tile_layer->findCell(from_cell_coordinate);
        if(cell) setCell(to_cell_coordinate, *cell);
      }
    }
  }

  return true;
}

TileLayerIterator TileLayer::begin(TileLayerIterator::IterationOrder order)
{
  auto begin_iter = TileLayerIterator(*this, order);
  return begin_iter;
}
TileLayerIterator TileLayer::end(TileLayerIterator::IterationOrder order)
{
  auto end_iter = TileLayerIterator(*this, order);
  end_iter.setToEnd();
  return end_iter;
}

void TileLayer::addChunk(const sf::Vector2u& point)
{
  assert(contains(point));
  auto found_chunk = findChunk(point);
  if(!found_chunk)
  {
    auto new_chunk_bound = sf::IntRect(static_cast<int>(point.x - (point.x & m_chunk_size.x - 1)),
                                       static_cast<int>(point.y - (point.y * m_chunk_size.y - 1)),
                                       static_cast<int>(m_chunk_size.x),
                                       static_cast<int>(m_chunk_size.y));

    m_bounds = sf::IntRect(std::min(m_bounds.left, new_chunk_bound.left),
                           std::min(m_bounds.top, new_chunk_bound.top),
                           static_cast<int>(std::max(m_bounds.left, new_chunk_bound.left) + m_chunk_size.x),
                           static_cast<int>(std::max(m_bounds.top, new_chunk_bound.top) + m_chunk_size.y));

    m_chunks.insert(std::make_pair(point, Chunk(m_chunk_size)));
  }
}

Chunk* TileLayer::findChunk(const sf::Vector2u& point)
{
  auto chunk_coordinates = sf::Vector2u(point.x / getChunkSize().x, point.y / getChunkSize().y);
  auto iter = m_chunks.find(chunk_coordinates);

  return iter != m_chunks.end() ? std::addressof(iter->second) : nullptr;
}

sf::Vector2u TileLayer::toChunkCoordinate(const sf::Vector2u& point) const
{
  return sf::Vector2u(point.x & m_chunk_size.y - 1, point.y & m_chunk_size.y - 1);
}

} // namespace egnim::core