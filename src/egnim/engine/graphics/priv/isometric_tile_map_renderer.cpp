/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/graphics/priv/isometric_tile_map_renderer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics::priv {

IsometricTileMapRenderer::IsometricTileMapRenderer(const TileMap &tile_map) :
  TileMapRenderer(tile_map)
{

}

IsometricTileMapRenderer::~IsometricTileMapRenderer() = default;

sf::Vector2f IsometricTileMapRenderer::tileToPixelCoords(unsigned x, unsigned y) const
{
  return sf::Vector2f();
}

sf::Vector2u IsometricTileMapRenderer::pixelToTileCoords(float x, float y) const
{
  return sf::Vector2u();
}


} // namespace egnim::graphics::priv
