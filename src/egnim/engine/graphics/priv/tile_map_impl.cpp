/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderTarget.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/graphics/priv/tile_map_impl.h>
#include <egnim/engine/graphics/group_layer.h>
#include <egnim/engine/graphics/tile_layer.h>
#include <egnim/engine/graphics/tileset.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics::priv {

static TileLayerIterator::IterationOrder tileMapOrderToTileLayerOrder(TileMap::RenderOrder render_order)
{
  switch(render_order)
  {
    case TileMap::RenderOrder::LeftUp:
      return TileLayerIterator::IterationOrder::LeftUp;

    case TileMap::RenderOrder::LeftDown:
      return TileLayerIterator::IterationOrder::LeftDown;

    case TileMap::RenderOrder::RightUp:
      return TileLayerIterator::IterationOrder::RightUp;

    default:
      return TileLayerIterator::IterationOrder::RightDown;
  }
}

TileMapImpl::TileMapImpl(TileMap::RenderOrder render_order, const sf::Vector2u& tile_size) :
  m_tile_size(tile_size),
  m_render_order(render_order),
  m_root_layer(std::make_unique<GroupLayer>())
{

}

TileMapImpl::~TileMapImpl() = default;

void TileMapImpl::setRenderOrder(TileMap::RenderOrder render_order)
{
  m_render_order = render_order;
}

TileMap::RenderOrder TileMapImpl::getRenderOrder() const
{
  return m_render_order;
}

void TileMapImpl::setTileSize(const sf::Vector2u& tile_size)
{
  m_tile_size = tile_size;
}

const sf::Vector2u& TileMapImpl::getTileSize() const
{
  return m_tile_size;
}

void TileMapImpl::attachTileset(std::unique_ptr<Tileset> tileset)
{
  assert(tileset);
  m_tilesets.push_back(std::move(tileset));
}

std::unique_ptr<Tileset> TileMapImpl::detachTileset(const Tileset& tileset)
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

const std::list<std::unique_ptr<Tileset>>& TileMapImpl::getTilesets() const
{
  return m_tilesets;
}

GroupLayer& TileMapImpl::getRootLayer()
{
  return *m_root_layer;
}

const GroupLayer& TileMapImpl::getRootLayer() const
{
  return *m_root_layer;
}

sf::Vector2f TileMapImpl::tileToPixelCoords(const sf::Vector2u& point) const
{
  return tileToPixelCoords(point.x, point.y);
}

sf::FloatRect TileMapImpl::tileToPixelCoords(const sf::Rect<unsigned>& area) const
{
  auto first_vec = tileToPixelCoords(sf::Vector2u(area.left, area.top));
  auto second_vec = tileToPixelCoords(sf::Vector2u(area.left + area.width, area.top + area.height));
  return sf::FloatRect(first_vec, second_vec - first_vec);
}

sf::Vector2u TileMapImpl::pixelToTileCoords(const sf::Vector2f& point) const
{
  return pixelToTileCoords(point.x, point.y);
}

void TileMapImpl::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  auto layer_iteration_order = tileMapOrderToTileLayerOrder(getRenderOrder());
  auto old_states_transform = states.transform;
  auto& root_layer = getRootLayer();
  for(auto& layer : root_layer)
  {
    if(layer.getType() != Layer::Type::TileLayer)
      continue;

    auto& tile_layer = dynamic_cast<const TileLayer&>(layer);
    for(auto tile_layer_iter = tile_layer.begin(layer_iteration_order);
        tile_layer_iter != tile_layer.end(layer_iteration_order); ++tile_layer_iter)
    {
      auto& cell = *tile_layer_iter;
      auto cell_point = tile_layer_iter.getCurrentPoint();
      auto pixel_coords = tileToPixelCoords(cell_point);

      states.transform = old_states_transform;
      states.transform.translate(pixel_coords);

      target.draw(cell, states);
    }
  }
}

} // namespace egnim::graphics::priv
