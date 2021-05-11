#ifndef ISOMETRIC_TILE_MAP_IMPL_H
#define ISOMETRIC_TILE_MAP_IMPL_H

/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/graphics/priv/tile_map_impl.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics::priv
{

  class IsometricTileMapImpl : public TileMapImpl
  {
  public:
    explicit IsometricTileMapImpl(TileMap::RenderOrder render_order, const sf::Vector2u& tile_size);
    ~IsometricTileMapImpl() override;

    [[nodiscard]] sf::Vector2f tileToPixelCoords(unsigned x, unsigned y) const override;
    [[nodiscard]] sf::Vector2u pixelToTileCoords(float x, float y) const override;

    [[nodiscard]] std::unique_ptr<TileMapImpl> clone() const override;

  private:
    [[nodiscard]] sf::Vector2f getHalfTileSize() const;
  };

} // namespace egnim::graphics::priv

#endif //ISOMETRIC_TILE_MAP_IMPL_H
