#ifndef TILE_LAYER_H
#define TILE_LAYER_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics//Rect.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <unordered_map>
#include <map>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/core/layer.h>
#include <egnim/engine/core/chunk.h>
#include <egnim/engine/core/cell.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

  class EGNIM_UTILITY_API TileLayer : public Layer
  {
  public:
    explicit TileLayer(const sf::Vector2u& size, const sf::Vector2u& chunk_size);
    ~TileLayer() override;

    void setSize(const sf::Vector2u& size);
    [[nodiscard]] const sf::Vector2u& getSize() const;
    [[nodiscard]] const sf::Vector2u& getChunkSize() const;

    [[nodiscard]] sf::IntRect getBounds() const;
    [[nodiscard]] sf::IntRect getRect() const;

    [[nodiscard]] bool contains(const sf::Vector2u& point) const;

    [[nodiscard]] const Chunk& getChunk(const sf::Vector2u& point) const;
    [[nodiscard]] const Chunk* findChunk(const sf::Vector2u& point) const;

    void setCell(const sf::Vector2u& point, const Cell& cell);
    [[nodiscard]] const Cell& getCell(const sf::Vector2u& point) const;
    [[nodiscard]] const Cell* findCell(const sf::Vector2u& point) const;

    [[nodiscard]] bool isEmpty() const override;
    [[nodiscard]] std::list<const Tileset*> getUsedTilesets() const override;
    [[nodiscard]] bool isUsedTileset(const Tileset& tileset) const override;

    [[nodiscard]] bool canMerge(const Layer& layer) const override;
    bool merge(const sf::Vector2u& point, const Layer& layer) override;

  private:
    void addChunk(const sf::Vector2u& point);

    [[nodiscard]] Chunk* findChunk(const sf::Vector2u& point);
    [[nodiscard]] sf::Vector2u toChunkCoordinate(const sf::Vector2u& point) const;

  private:
    sf::Vector2u m_size;
    sf::Vector2u m_chunk_size;
    sf::IntRect m_bounds;
    std::map<sf::Vector2u, Chunk> m_chunks;
    std::unordered_map<const Tileset*, unsigned> m_used_tilesets;
  };

} // namespace egnim::core

#endif //TILE_LAYER_H
