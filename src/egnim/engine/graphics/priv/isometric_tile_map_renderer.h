#ifndef ISOMETRIC_TILE_MAP_RENDERER_H
#define ISOMETRIC_TILE_MAP_RENDERER_H

/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/graphics/priv/tile_map_renderer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics::priv
{

  class IsometricTileMapRenderer : public TileMapRenderer
  {
  public:
    explicit IsometricTileMapRenderer(const TileMap& tile_map);
    ~IsometricTileMapRenderer() override;
  };

} // namespace egnim::graphics::priv

#endif //ISOMETRIC_TILE_MAP_RENDERER_H
