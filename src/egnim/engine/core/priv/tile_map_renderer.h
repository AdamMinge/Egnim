#ifndef TILE_MAP_RENDERER_H
#define TILE_MAP_RENDERER_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Drawable.hpp>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{
  class TileMap;
}

namespace egnim::core::priv
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

} // namespace egnim::core::priv

#endif //TILE_MAP_RENDERER_H
