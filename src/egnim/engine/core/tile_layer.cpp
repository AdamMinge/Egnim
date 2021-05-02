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

const Chunk& TileLayer::getChunk(const sf::Vector2u& point)
{
  auto chunk_coordinates = sf::Vector2u(point.x / getChunkSize().x, point.y / getChunkSize().y);
  auto chunk = findChunk(chunk_coordinates);

  assert(chunk);

  return *chunk;
}

const Chunk* TileLayer::findChunk(const sf::Vector2u& point)
{
  auto chunk_coordinates = sf::Vector2u(point.x / getChunkSize().x, point.y / getChunkSize().y);
  auto iter = m_chunks.find(chunk_coordinates);

  return iter != m_chunks.end() ? std::addressof(iter->second) : nullptr;
}

void TileLayer::setCell(const sf::Vector2u& point, const Cell& cell)
{
  //////////////////////////////////////////// TO DO ////////////////////////////////////////////
}

const Cell& TileLayer::getCell(const sf::Vector2u& point)
{
  //////////////////////////////////////////// TO DO ////////////////////////////////////////////
}

const Cell* TileLayer::findCell(const sf::Vector2u& point)
{
  //////////////////////////////////////////// TO DO ////////////////////////////////////////////
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

bool TileLayer::canMergeWith(const Layer& layer) const
{
  return layer.getType() == getType();
}

bool TileLayer::mergeWith(const Layer& layer)
{
  assert(canMergeWith(layer));
  //////////////////////////////////////////// TO DO ////////////////////////////////////////////
}

} // namespace egnim::core