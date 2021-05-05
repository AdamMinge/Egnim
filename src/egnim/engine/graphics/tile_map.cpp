/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderTarget.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/graphics/tile_map.h>
#include <egnim/engine/graphics/tileset.h>
#include <egnim/engine/graphics/priv/orthogonal_tile_map_impl.h>
#include <egnim/engine/graphics/priv/isometric_tile_map_impl.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics
{

TileMap::TileMap(Orientation orientation, RenderOrder render_order, const sf::Vector2u &tile_size)
  :
  m_orientation(orientation),
  m_tile_map_impl(createImpl(orientation, render_order, tile_size))
{

}

TileMap::~TileMap() = default;

void TileMap::setOrientation(Orientation orientation)
{
  if (m_orientation != orientation) {
    assert(m_tile_map_impl);
    m_tile_map_impl = createImpl(orientation,m_tile_map_impl->getRenderOrder(),m_tile_map_impl->getTileSize());
    m_orientation = orientation;
  }
}

TileMap::Orientation TileMap::getOrientation() const
{
  return m_orientation;
}

void TileMap::setRenderOrder(RenderOrder render_order)
{
  m_tile_map_impl->setRenderOrder(render_order);
}

TileMap::RenderOrder TileMap::getRenderOrder() const
{
  return m_tile_map_impl->getRenderOrder();
}

void TileMap::setTileSize(const sf::Vector2u &tile_size)
{
  m_tile_map_impl->setTileSize(tile_size);
}

const sf::Vector2u& TileMap::getTileSize() const
{
  return m_tile_map_impl->getTileSize();
}

void TileMap::attachTileset(std::unique_ptr<Tileset> tileset)
{
  m_tile_map_impl->attachTileset(std::move(tileset));
}

std::unique_ptr<Tileset> TileMap::detachTileset(const Tileset& tileset)
{
  return m_tile_map_impl->detachTileset(tileset);
}

const std::list<std::unique_ptr<Tileset>>& TileMap::getTilesets() const
{
  return m_tile_map_impl->getTilesets();
}

GroupLayer& TileMap::getRootLayer()
{
  return m_tile_map_impl->getRootLayer();
}

const GroupLayer& TileMap::getRootLayer() const
{
  return m_tile_map_impl->getRootLayer();
}

sf::Vector2f TileMap::tileToPixelCoords(unsigned x, unsigned y) const
{
  return m_tile_map_impl->tileToPixelCoords(x, y);
}

sf::Vector2f TileMap::tileToPixelCoords(const sf::Vector2u& point) const
{
  return m_tile_map_impl->tileToPixelCoords(point);
}

sf::FloatRect TileMap::tileToPixelCoords(const sf::Rect<unsigned>& area) const
{
  return m_tile_map_impl->tileToPixelCoords(area);
}

sf::Vector2u TileMap::pixelToTileCoords(float x, float y) const
{
  return m_tile_map_impl->pixelToTileCoords(x, y);
}

sf::Vector2u TileMap::pixelToTileCoords(const sf::Vector2f& point) const
{
  return m_tile_map_impl->pixelToTileCoords(point);
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(*m_tile_map_impl, states);
}

std::unique_ptr<priv::TileMapImpl> TileMap::createImpl(
  Orientation orientation, RenderOrder render_order, const sf::Vector2u& tile_size)
{
  if(orientation == Orientation::Isometric)
    return std::make_unique<priv::IsometricTileMapImpl>(render_order, tile_size);
  else
    return std::make_unique<priv::OrthogonalTileMapImpl>(render_order, tile_size);
}

} // namespace egnim::graphics