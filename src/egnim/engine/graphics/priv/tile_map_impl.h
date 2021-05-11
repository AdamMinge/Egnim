#ifndef TILE_MAP_IMPL_H
#define TILE_MAP_IMPL_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/graphics/tile_map.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics
{
  class TileMap;
  class GroupLayer;
}

namespace egnim::graphics::priv
{

  class TileMapImpl : public sf::Drawable
  {
  public:
    explicit TileMapImpl(TileMap::RenderOrder render_order, const sf::Vector2u& tile_size);
    ~TileMapImpl() override;

    void setRenderOrder(TileMap::RenderOrder render_order);
    [[nodiscard]] TileMap::RenderOrder getRenderOrder() const;

    void setTileSize(const sf::Vector2u& tile_size);
    [[nodiscard]] const sf::Vector2u& getTileSize() const;

    void attachTileset(std::shared_ptr<Tileset> tileset);
    [[nodiscard]] std::shared_ptr<Tileset> detachTileset(const Tileset& tileset);
    [[nodiscard]] const std::list<std::shared_ptr<Tileset>>& getTilesets() const;

    [[nodiscard]] GroupLayer& getRootLayer();
    [[nodiscard]] const GroupLayer& getRootLayer() const;

    [[nodiscard]] virtual sf::Vector2f tileToPixelCoords(unsigned x, unsigned y) const = 0;
    [[nodiscard]] sf::Vector2f tileToPixelCoords(const sf::Vector2u& point) const;
    [[nodiscard]] sf::FloatRect tileToPixelCoords(const sf::Rect<unsigned>& area) const;

    [[nodiscard]] virtual sf::Vector2u pixelToTileCoords(float x, float y) const = 0;
    [[nodiscard]] sf::Vector2u pixelToTileCoords(const sf::Vector2f& point) const;

    [[nodiscard]] virtual std::unique_ptr<TileMapImpl> clone() const = 0;

  protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void initializeClone(TileMapImpl& tile_map_impl) const;

  private:
    sf::Vector2u m_tile_size;
    TileMap::RenderOrder m_render_order;
    std::unique_ptr<GroupLayer> m_root_layer;
    std::list<std::shared_ptr<Tileset>> m_tilesets;
  };

} // namespace egnim::graphics::priv

#endif //TILE_MAP_IMPL_H
