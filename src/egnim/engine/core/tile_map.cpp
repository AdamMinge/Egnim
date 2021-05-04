/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/core/tile_map.h>
#include <egnim/engine/core/group_layer.h>
#include <egnim/engine/core/tileset.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core {

TileMap::TileMap(Orientation orientation, RenderOrder render_order) :
  m_orientation(orientation),
  m_render_order(render_order),
  m_root_layer(std::make_unique<GroupLayer>())
{

}

TileMap::~TileMap() = default;

void TileMap::setOrientation(Orientation orientation)
{
  m_orientation = orientation;
}

TileMap::Orientation TileMap::getOrientation() const
{
  return m_orientation;
}

void TileMap::setRenderOrder(RenderOrder render_order)
{
  m_render_order = render_order;
}

TileMap::RenderOrder TileMap::getRenderOrder() const
{
  return m_render_order;
}

void TileMap::attachTileset(std::unique_ptr<Tileset> tileset)
{
  assert(tileset);
  m_tilesets.push_back(std::move(tileset));
}

std::unique_ptr<Tileset> TileMap::detachTileset(const Tileset& tileset)
{
  auto found = std::find_if(m_tilesets.begin(), m_tilesets.end(), [&tileset](auto &current_tileset)
  {
    return current_tileset.get() == std::addressof(tileset);
  });

  if (found == m_tilesets.end())
    return nullptr;

  auto found_tileset = std::move(*found);
  m_tilesets.erase(found);
  return found_tileset;
}

const std::list<std::unique_ptr<Tileset>>& TileMap::getTilesets() const
{
  return m_tilesets;
}

GroupLayer& TileMap::getRootLayer()
{
  return *m_root_layer;
}

const GroupLayer& TileMap::getRootLayer() const
{
  return *m_root_layer;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

} // namespace egnim::core