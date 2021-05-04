/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/priv/isometric_tile_map_renderer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core::priv {

IsometricTileMapRenderer::IsometricTileMapRenderer(const TileMap &tile_map) :
  TileMapRenderer(tile_map)
{

}

IsometricTileMapRenderer::~IsometricTileMapRenderer() = default;

} // namespace egnim::core::priv
