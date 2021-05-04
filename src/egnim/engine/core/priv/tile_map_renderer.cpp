/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/priv/tile_map_renderer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core::priv {

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

} // namespace egnim::core::priv
