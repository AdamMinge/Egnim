/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderTarget.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/graphics/priv/tile_map_renderer.h>
#include <egnim/engine/graphics/tile_map.h>
#include <egnim/engine/graphics/group_layer.h>
#include <egnim/engine/graphics/tile_layer.h>
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

TileMapRenderer::TileMapRenderer(const TileMap &tile_map) :
  m_tile_map(tile_map)
{

}

TileMapRenderer::~TileMapRenderer() = default;

const TileMap& TileMapRenderer::getTileMap() const
{
  return m_tile_map;
}

sf::Vector2f TileMapRenderer::tileToPixelCoords(const sf::Vector2u& point) const
{
  return tileToPixelCoords(point.x, point.y);
}

sf::FloatRect TileMapRenderer::tileToPixelCoords(const sf::Rect<unsigned>& area) const
{
  auto first_vec = tileToPixelCoords(sf::Vector2u(area.left, area.top));
  auto second_vec = tileToPixelCoords(sf::Vector2u(area.left + area.width, area.top + area.height));
  return sf::FloatRect(first_vec, second_vec - first_vec);
}

sf::Vector2u TileMapRenderer::pixelToTileCoords(const sf::Vector2f& point) const
{
  return pixelToTileCoords(point.x, point.y);
}

void TileMapRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  auto layer_iteration_order = tileMapOrderToTileLayerOrder(m_tile_map.getRenderOrder());
  auto old_states_transform = states.transform;
  auto& root_layer = m_tile_map.getRootLayer();
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
