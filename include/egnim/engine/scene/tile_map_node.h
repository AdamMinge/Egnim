#ifndef TILE_MAP_NODE_H
#define TILE_MAP_NODE_H

/* --------------------------------- Standard ------------------------------- */
#include <map>
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/scene/node.h>
#include <egnim/engine/graphics/tile_map.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{

  class EGNIM_UTILITY_API TileMapNode : public Node
  {
    EGNIM_CLASS(TileMapNode, Node)

  public:
    explicit TileMapNode();
    ~TileMapNode() override;

    [[nodiscard]] graphics::TileMap& getTileMap();
    [[nodiscard]] const graphics::TileMap& getTileMap() const;

    void accept(SceneVisitor& visitor) override;

  protected:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

  private:
    graphics::TileMap m_tile_map;
  };

} // namespace egnim::scene

#endif //TILE_MAP_NODE_H
