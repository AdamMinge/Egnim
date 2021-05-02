#ifndef CHUNK_H
#define CHUNK_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <vector>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/core/cell.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

  class EGNIM_UTILITY_API Chunk : public sf::Drawable
  {
  public:
    explicit Chunk(const sf::Vector2u& size);
    ~Chunk() override;

    Chunk(const Chunk& other);
    Chunk(Chunk&& other) noexcept;

    Chunk& operator=(const Chunk& other);
    Chunk& operator=(Chunk&& other) noexcept;

    void setCell(const sf::Vector2u& point, const Cell& cell);
    [[nodiscard]] const Cell& getCell(const sf::Vector2u& point);
    [[nodiscard]] const Cell* findCell(const sf::Vector2u& point);

    [[nodiscard]] bool contains(const sf::Vector2u& point);
    [[nodiscard]] bool isEmpty() const;

    [[nodiscard]] std::vector<Cell>::iterator begin();
    [[nodiscard]] std::vector<Cell>::const_iterator begin() const;

    [[nodiscard]] std::vector<Cell>::iterator end();
    [[nodiscard]] std::vector<Cell>::const_iterator end() const;

  protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  private:
    std::vector<Cell> m_grid;
    sf::Vector2u m_size;
  };

} // namespace egnim::core

#endif //CHUNK_H
