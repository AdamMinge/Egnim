#ifndef TILE_H
#define TILE_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <vector>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics
{

  class Tileset;

  class EGNIM_UTILITY_API Tile  : public sf::Drawable
  {
    friend Tileset;

  public:
    ~Tile() override;

    [[nodiscard]] const Tileset& getTileset() const;
    [[nodiscard]] unsigned getId() const;

    [[nodiscard]] sf::Vector2u getSize() const;

  protected:
    explicit Tile(Tileset& tileset, sf::Sprite sprite, unsigned id);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  private:
    Tileset& m_tileset;
    sf::Sprite m_sprite;
    unsigned m_id;
  };

} // namespace egnim::graphics

#endif //TILE_H
