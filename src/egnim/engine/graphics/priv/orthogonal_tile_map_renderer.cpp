/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/graphics/priv/orthogonal_tile_map_renderer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics::priv {

OrthogonalTileMapRenderer::OrthogonalTileMapRenderer(const TileMap &tile_map) :
  TileMapRenderer(tile_map)
{

}

OrthogonalTileMapRenderer::~OrthogonalTileMapRenderer() = default;

} // namespace egnim::graphics::priv
