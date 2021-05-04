/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/graphics/priv/orthogonal_tile_map_renderer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics::priv {

OrthogonalTileMapRenderer::OrthogonalTileMapRenderer(const TileMap &tile_map) :
  TileMapRenderer(tile_map)
{

}

OrthogonalTileMapRenderer::~OrthogonalTileMapRenderer() = default;

sf::Vector2f OrthogonalTileMapRenderer::tileToPixelCoords(unsigned x, unsigned y) const
{
  return sf::Vector2f();
}

sf::Vector2u OrthogonalTileMapRenderer::pixelToTileCoords(float x, float y) const
{
  return sf::Vector2u();
}

} // namespace egnim::graphics::priv
