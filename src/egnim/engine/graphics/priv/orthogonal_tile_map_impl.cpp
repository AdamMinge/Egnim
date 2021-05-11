/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/graphics/priv/orthogonal_tile_map_impl.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics::priv {

OrthogonalTileMapImpl::OrthogonalTileMapImpl(TileMap::RenderOrder render_order, const sf::Vector2u& tile_size) :
  TileMapImpl(render_order, tile_size)
{

}

OrthogonalTileMapImpl::~OrthogonalTileMapImpl() = default;

sf::Vector2f OrthogonalTileMapImpl::tileToPixelCoords(unsigned x, unsigned y) const
{
  return sf::Vector2f(
    static_cast<float>(x * getTileSize().x),
    static_cast<float>(y * getTileSize().y)
  );
}

sf::Vector2u OrthogonalTileMapImpl::pixelToTileCoords(float x, float y) const
{
  assert(x >= 0 && y >= 0);
  assert(getTileSize().x != 0u && getTileSize().y != 0u);

  return sf::Vector2u(
    static_cast<unsigned>(x / static_cast<float>(getTileSize().x)),
    static_cast<unsigned>(y / static_cast<float>(getTileSize().y))
  );
}

std::unique_ptr<TileMapImpl> OrthogonalTileMapImpl::clone() const
{
  auto clone_tile_map_impl = std::make_unique<OrthogonalTileMapImpl>(getRenderOrder(), getTileSize());
  return clone_tile_map_impl;
}

} // namespace egnim::graphics::priv
