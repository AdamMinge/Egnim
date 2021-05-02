#ifndef CELL_H
#define CELL_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Drawable.hpp>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

  class Tile;
  class Tileset;

  class EGNIM_UTILITY_API Cell : public sf::Drawable
  {
  public:
    explicit Cell(const Tile* tile = nullptr);
    ~Cell() override;

    Cell(const Cell& other);
    Cell(Cell&& other) noexcept;

    Cell& operator=(const Cell& other);
    Cell& operator=(Cell&& other) noexcept;

    void setTile(const Tile* tile);

    [[nodiscard]] const Tile* getTile() const;
    [[nodiscard]] const Tileset* getTileset() const;

    [[nodiscard]] bool isEmpty() const;

  protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  private:
    const Tile* m_tile;
  };

} // namespace egnim::core

#endif //CELL_H
