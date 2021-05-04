#ifndef TILE_MAP_RENDERER_H
#define TILE_MAP_RENDERER_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Drawable.hpp>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics
{
  class TileMap;
}

namespace egnim::graphics::priv
{

  class TileMapRenderer : public sf::Drawable
  {
  public:
    explicit TileMapRenderer(const TileMap& tile_map);
    ~TileMapRenderer() override;

    [[nodiscard]] const TileMap& getTileMap() const;

  protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  private:
    const TileMap& m_tile_map;
  };

} // namespace egnim::graphics::priv

#endif //TILE_MAP_RENDERER_H
