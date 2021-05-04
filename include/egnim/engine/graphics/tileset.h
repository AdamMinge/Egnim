#ifndef TILESET_H
#define TILESET_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <unordered_map>
#include <memory>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics
{

  class Tile;

  class EGNIM_UTILITY_API Tileset
  {
  public:
    explicit Tileset(sf::Texture& texture, const sf::Vector2u& tile_size, unsigned spacing, unsigned margin);
    ~Tileset();

    void setTileSize(const sf::Vector2u& tile_size);
    [[nodiscard]] const sf::Vector2u& getTileSize() const;

    void setSpacing(unsigned spacing);
    [[nodiscard]] unsigned getSpacing() const;

    void setMargin(unsigned margin);
    [[nodiscard]] unsigned getMargin() const;

    [[nodiscard]] const Tile& getTile(unsigned id) const;
    [[nodiscard]] unsigned getTileCount() const;

    [[nodiscard]] unsigned getColumnCount() const;
    [[nodiscard]] unsigned getRowCount() const;

    [[nodiscard]] bool contains(const Tile& tile) const;

  private:
    void init();

    template<typename TYPE>
    void changeValue(TYPE& prev_value, const TYPE& new_value);

  private:
    std::unordered_map<unsigned, std::unique_ptr<Tile>> m_tiles;
    sf::Texture& m_texture;
    sf::Vector2u m_tile_size;
    unsigned m_spacing;
    unsigned m_margin;

    unsigned m_column_count;
    unsigned m_row_count;
  };

  template<typename TYPE>
  void Tileset::changeValue(TYPE& prev_value, const TYPE& new_value)
  {
    if(prev_value != new_value)
    {
      prev_value = new_value;
      init();
    }
  }

} // namespace egnim::graphics

#endif //TILESET_H
