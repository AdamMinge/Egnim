#ifndef ISOMETRIC_TILE_MAP_RENDERER_H
#define ISOMETRIC_TILE_MAP_RENDERER_H

/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/core/priv/tile_map_renderer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core::priv
{

  class IsometricTileMapRenderer : public TileMapRenderer
  {
  public:
    explicit IsometricTileMapRenderer(const TileMap& tile_map);
    ~IsometricTileMapRenderer() override;
  };

}

#endif //ISOMETRIC_TILE_MAP_RENDERER_H
