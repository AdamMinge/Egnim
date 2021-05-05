/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/graphics/priv/isometric_tile_map_impl.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics::priv {

IsometricTileMapImpl::IsometricTileMapImpl(TileMap::RenderOrder render_order, const sf::Vector2u& tile_size) :
  TileMapImpl(render_order, tile_size)
{

}

IsometricTileMapImpl::~IsometricTileMapImpl() = default;

sf::Vector2f IsometricTileMapImpl::tileToPixelCoords(unsigned x, unsigned y) const
{
  auto half_tile_size = getHalfTileSize();
  return sf::Vector2f(
    static_cast<float>(x - y) * half_tile_size.x,
    static_cast<float>(x + y) * half_tile_size.y
    );
}

sf::Vector2u IsometricTileMapImpl::pixelToTileCoords(float x, float y) const
{
  auto half_tile_size = getHalfTileSize();
  assert((x / half_tile_size.x) + (y / half_tile_size.y) >= 0);
  assert((y / half_tile_size.y) - (x / half_tile_size.x) >= 0);

  return sf::Vector2u(
    static_cast<unsigned>(((x / half_tile_size.x) + (y / half_tile_size.y)) * 0.5f),
    static_cast<unsigned>(((y / half_tile_size.y) - (x / half_tile_size.x)) * 0.5f)
  );
}

sf::Vector2f IsometricTileMapImpl::getHalfTileSize() const
{
  return sf::Vector2f(
    static_cast<float>(getTileSize().x) * 0.5f,
    static_cast<float>(getTileSize().y) * 0.5f
  );
}


} // namespace egnim::graphics::priv
