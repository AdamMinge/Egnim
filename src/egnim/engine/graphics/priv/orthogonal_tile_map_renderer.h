#ifndef ORTHOGONAL_TILE_MAP_RENDERER_H
#define ORTHOGONAL_TILE_MAP_RENDERER_H

/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/graphics/priv/tile_map_renderer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics::priv
{

  class OrthogonalTileMapRenderer : public TileMapRenderer
  {
  public:
    explicit OrthogonalTileMapRenderer(const TileMap& tile_map);
    ~OrthogonalTileMapRenderer() override;

    [[nodiscard]] sf::Vector2f tileToPixelCoords(unsigned x, unsigned y) const override;
    [[nodiscard]] sf::Vector2u pixelToTileCoords(float x, float y) const override;
  };

} // namespace egnim::graphics::priv

#endif //ORTHOGONAL_TILE_MAP_RENDERER_H
