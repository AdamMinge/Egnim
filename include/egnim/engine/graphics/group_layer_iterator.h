#ifndef GROUP_LAYER_ITERATOR_H
#define GROUP_LAYER_ITERATOR_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <iterator>
#include <queue>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics
{

  class Layer;
  class GroupLayer;

  class EGNIM_UTILITY_API GroupLayerIterator
  {
    friend class GroupLayer;

  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using pointer           = Layer*;
    using reference         = Layer&;

  public:
    ~GroupLayerIterator();

    GroupLayerIterator(const GroupLayerIterator&) = default;
    GroupLayerIterator(GroupLayerIterator&&) = default;

    GroupLayerIterator& operator=(const GroupLayerIterator&) = default;
    GroupLayerIterator& operator=(GroupLayerIterator&&) = default;

    reference operator*() const;
    pointer operator->();

    GroupLayerIterator& operator++();
    GroupLayerIterator operator++(int); // NOLINT(cert-dcl21-cpp)

    [[nodiscard]] bool operator==(const GroupLayerIterator& other) const;
    [[nodiscard]] bool operator!=(const GroupLayerIterator& other) const;

  private:
    explicit GroupLayerIterator(GroupLayer* group_layer);
    explicit GroupLayerIterator(std::queue<Layer*> layers_queue);

    void advance();

  private:
    std::queue<Layer*> m_layers_queue;
  };

  class EGNIM_UTILITY_API ConstGroupLayerIterator
  {
    friend class GroupLayer;

  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using pointer           = const Layer*;
    using reference         = const Layer&;

  public:
    ~ConstGroupLayerIterator();

    ConstGroupLayerIterator(const ConstGroupLayerIterator&) = default;
    ConstGroupLayerIterator(ConstGroupLayerIterator&&) = default;

    ConstGroupLayerIterator& operator=(const ConstGroupLayerIterator&) = default;
    ConstGroupLayerIterator& operator=(ConstGroupLayerIterator&&) = default;

    reference operator*() const;
    pointer operator->();

    ConstGroupLayerIterator& operator++();
    ConstGroupLayerIterator operator++(int); // NOLINT(cert-dcl21-cpp)

    [[nodiscard]] bool operator==(const ConstGroupLayerIterator& other) const;
    [[nodiscard]] bool operator!=(const ConstGroupLayerIterator& other) const;

  private:
    explicit ConstGroupLayerIterator(const GroupLayer* group_layer);
    explicit ConstGroupLayerIterator(std::queue<const Layer*> layers_queue);

    void advance();

  private:
    std::queue<const Layer*> m_layers_queue;
  };

} // namespace egnim::graphics

#endif //GROUP_LAYER_ITERATOR_H
