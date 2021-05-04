#ifndef ORTHOGONAL_TILE_MAP_RENDERER_H
#define ORTHOGONAL_TILE_MAP_RENDERER_H

/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/core/priv/tile_map_renderer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core::priv
{

  class OrthogonalTileMapRenderer : public TileMapRenderer
  {
  public:
    explicit OrthogonalTileMapRenderer(const TileMap& tile_map);
    ~OrthogonalTileMapRenderer() override;
  };

}

#endif //ORTHOGONAL_TILE_MAP_RENDERER_H
