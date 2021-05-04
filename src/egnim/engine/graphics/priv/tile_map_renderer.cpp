/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/graphics/priv/tile_map_renderer.h>
#include <egnim/engine/graphics/tile_map.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics::priv {

TileMapRenderer::TileMapRenderer(const TileMap &tile_map) :
  m_tile_map(tile_map)
{

}

TileMapRenderer::~TileMapRenderer() = default;

const TileMap& TileMapRenderer::getTileMap() const
{
  return m_tile_map;
}

void TileMapRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  auto& root_layer = m_tile_map.getRootLayer();

}

} // namespace egnim::graphics::priv
