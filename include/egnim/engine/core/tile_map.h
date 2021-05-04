#ifndef TILE_MAP_H
#define TILE_MAP_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Drawable.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <list>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

  class GroupLayer;
  class Tileset;

  class EGNIM_UTILITY_API TileMap : public sf::Drawable
  {
  public:
    enum class RenderOrder;
    enum class Orientation;

  public:
    explicit TileMap(Orientation orientation, RenderOrder render_order);
    ~TileMap();

    void setOrientation(Orientation orientation);
    [[nodiscard]] Orientation getOrientation() const;

    void setRenderOrder(RenderOrder render_order);
    [[nodiscard]] RenderOrder getRenderOrder() const;

    void attachTileset(std::unique_ptr<Tileset> tileset);
    [[nodiscard]] std::unique_ptr<Tileset> detachTileset(const Tileset& tileset);
    [[nodiscard]] const std::list<std::unique_ptr<Tileset>>& getTilesets() const;

    [[nodiscard]] GroupLayer& getRootLayer();
    [[nodiscard]] const GroupLayer& getRootLayer() const;

  protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  private:
    RenderOrder m_render_order;
    Orientation m_orientation;
    std::unique_ptr<GroupLayer> m_root_layer;
    std::list<std::unique_ptr<Tileset>> m_tilesets;
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

} // namespace egnim::core

#endif //TILE_MAP_H
