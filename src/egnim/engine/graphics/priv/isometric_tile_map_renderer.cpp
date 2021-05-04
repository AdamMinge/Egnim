/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/graphics/priv/isometric_tile_map_renderer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics::priv {

IsometricTileMapRenderer::IsometricTileMapRenderer(const TileMap &tile_map) :
  TileMapRenderer(tile_map)
{

}

IsometricTileMapRenderer::~IsometricTileMapRenderer() = default;

} // namespace egnim::graphics::priv
