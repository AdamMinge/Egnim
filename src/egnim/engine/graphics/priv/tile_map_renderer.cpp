/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/graphics/priv/tile_map_renderer.h>
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

}

} // namespace egnim::graphics::priv
