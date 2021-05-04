/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/priv/orthogonal_tile_map_renderer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core::priv {

OrthogonalTileMapRenderer::OrthogonalTileMapRenderer(const TileMap &tile_map) :
  TileMapRenderer(tile_map)
{

}

OrthogonalTileMapRenderer::~OrthogonalTileMapRenderer() = default;

} // namespace egnim::core::priv
