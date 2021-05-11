#ifndef TILE_MAP_H
#define TILE_MAP_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML//Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <list>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics
{

  class GroupLayer;
  class Tileset;
  namespace priv { class TileMapImpl; }

  class EGNIM_UTILITY_API TileMap : public sf::Drawable , public sf::Transformable
  {
  public:
    enum class RenderOrder;
    enum class Orientation;

  public:
    explicit TileMap(Orientation orientation, RenderOrder render_order, const sf::Vector2u& tile_size);
    ~TileMap() override;

    TileMap(const TileMap& other);
    TileMap& operator=(const TileMap& other);

    void setOrientation(Orientation orientation);
    [[nodiscard]] Orientation getOrientation() const;

    void setRenderOrder(RenderOrder render_order);
    [[nodiscard]] RenderOrder getRenderOrder() const;

    void setTileSize(const sf::Vector2u& tile_size);
    [[nodiscard]] const sf::Vector2u& getTileSize() const;

    void attachTileset(std::shared_ptr<Tileset> tileset);
    [[nodiscard]] std::shared_ptr<Tileset> detachTileset(const Tileset& tileset);
    [[nodiscard]] const std::list<std::shared_ptr<Tileset>>& getTilesets() const;

    [[nodiscard]] GroupLayer& getRootLayer();
    [[nodiscard]] const GroupLayer& getRootLayer() const;

    [[nodiscard]] sf::Vector2f tileToPixelCoords(unsigned x, unsigned y) const;
    [[nodiscard]] sf::Vector2f tileToPixelCoords(const sf::Vector2u& point) const;
    [[nodiscard]] sf::FloatRect tileToPixelCoords(const sf::Rect<unsigned>& area) const;

    [[nodiscard]] sf::Vector2u pixelToTileCoords(float x, float y) const;
    [[nodiscard]] sf::Vector2u pixelToTileCoords(const sf::Vector2f& point) const;

  protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    [[nodiscard]] static std::unique_ptr<priv::TileMapImpl> createImpl(
      Orientation orientation, RenderOrder render_order, const sf::Vector2u& tile_size);

  private:
    TileMap::Orientation m_orientation;
    std::unique_ptr<priv::TileMapImpl> m_tile_map_impl;
  };

  enum class TileMap::RenderOrder
  {
    RightDown,
    RightUp,
    LeftDown,
    LeftUp
  };

  enum class TileMap::Orientation
  {
    Orthogonal,
    Isometric
  };

} // namespace egnim::graphics

#endif //TILE_MAP_H
