#ifndef TILE_LAYER_ITERATOR_H
#define TILE_LAYER_ITERATOR_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <iterator>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

  class TileLayer;
  class Cell;

  class EGNIM_UTILITY_API TileLayerIterator
  {
    friend TileLayer;

  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using pointer           = const Cell*;
    using reference         = const Cell&;

    enum class IterationOrder;

  public:
    ~TileLayerIterator();

    TileLayerIterator(const TileLayerIterator&) = default;
    TileLayerIterator(TileLayerIterator&&) = default;

    TileLayerIterator& operator=(const TileLayerIterator&) = default;
    TileLayerIterator& operator=(TileLayerIterator&&) = default;

    [[nodiscard]] IterationOrder getIterationOrder() const;
    [[nodiscard]] sf::Vector2u getCurrentPoint() const;

    reference operator*() const;
    pointer operator->();

    TileLayerIterator& operator++();
    TileLayerIterator operator++(int); // NOLINT(cert-dcl21-cpp)

    bool operator==(const TileLayerIterator& other) const;
    bool operator!=(const TileLayerIterator& other) const;

  private:
    explicit TileLayerIterator(TileLayer& tile_layer, IterationOrder iteration_order, bool end = false);
    void advance(TileLayerIterator& iter);

    [[nodiscard]] sf::Vector2u getFirstPoint() const;
    [[nodiscard]] sf::Vector2u getLastPoint() const;

  private:
    TileLayer* m_tile_layer;
    sf::Vector2u m_current_point;
    IterationOrder m_iteration_order;
    bool m_end;
  };

  enum class TileLayerIterator::IterationOrder
  {
    RightDown,
    RightUp,
    LeftDown,
    LeftUp
  };

} // namespace egnim::scene

#endif //TILE_LAYER_ITERATOR_H
