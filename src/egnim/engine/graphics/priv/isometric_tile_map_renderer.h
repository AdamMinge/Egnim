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

    [[nodiscard]] sf::Vector2f tileToPixelCoords(unsigned x, unsigned y) const override;
    [[nodiscard]] sf::Vector2u pixelToTileCoords(float x, float y) const override;
  };

} // namespace egnim::graphics::priv

#endif //ISOMETRIC_TILE_MAP_RENDERER_H
