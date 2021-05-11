#ifndef ORTHOGONAL_TILE_MAP_IMPL_H
#define ORTHOGONAL_TILE_MAP_IMPL_H

/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/graphics/priv/tile_map_impl.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics::priv
{

  class OrthogonalTileMapImpl : public TileMapImpl
  {
  public:
    explicit OrthogonalTileMapImpl(TileMap::RenderOrder render_order, const sf::Vector2u& tile_size);
    ~OrthogonalTileMapImpl() override;

    [[nodiscard]] sf::Vector2f tileToPixelCoords(unsigned x, unsigned y) const override;
    [[nodiscard]] sf::Vector2u pixelToTileCoords(float x, float y) const override;

    [[nodiscard]] std::unique_ptr<TileMapImpl> clone() const override;
  };

} // namespace egnim::graphics::priv

#endif //ORTHOGONAL_TILE_MAP_IMPL_H
