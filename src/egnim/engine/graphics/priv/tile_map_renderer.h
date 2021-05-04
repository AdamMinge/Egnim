#ifndef TILE_MAP_RENDERER_H
#define TILE_MAP_RENDERER_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics
{
  class TileMap;
  class GroupLayer;
}

namespace egnim::graphics::priv
{

  class TileMapRenderer : public sf::Drawable
  {
  public:
    explicit TileMapRenderer(const TileMap& tile_map);
    ~TileMapRenderer() override;

    [[nodiscard]] const TileMap& getTileMap() const;

    [[nodiscard]] virtual sf::Vector2f tileToPixelCoords(unsigned x, unsigned y) const = 0;
    [[nodiscard]] sf::Vector2f tileToPixelCoords(const sf::Vector2u& point) const;
    [[nodiscard]] sf::FloatRect tileToPixelCoords(const sf::Rect<unsigned>& area) const;

    [[nodiscard]] virtual sf::Vector2u pixelToTileCoords(float x, float y) const = 0;
    [[nodiscard]] sf::Vector2u pixelToTileCoords(const sf::Vector2f& point) const;

  protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  private:
    const TileMap& m_tile_map;
  };

} // namespace egnim::graphics::priv

#endif //TILE_MAP_RENDERER_H
