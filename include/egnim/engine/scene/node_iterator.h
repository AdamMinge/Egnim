#ifndef NODE_ITERATOR_H
#define NODE_ITERATOR_H

/* --------------------------------- Standard ------------------------------- */
#include <iterator>
#include <memory>
#include <queue>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{

  class Node;

  class EGNIM_UTILITY_API NodeIterator
  {
    friend class Node;

  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = std::unique_ptr<Node>;
    using pointer           = Node*;
    using reference         = Node&;

  public:
    ~NodeIterator();

    NodeIterator(const NodeIterator&) = default;
    NodeIterator(NodeIterator&&) = default;

    NodeIterator& operator=(const NodeIterator&) = default;
    NodeIterator& operator=(NodeIterator&&) = default;

    reference operator*() const;
    pointer operator->();

    NodeIterator& operator++();
    NodeIterator operator++(int); // NOLINT(cert-dcl21-cpp)

    bool operator==(const NodeIterator& other) const;
    bool operator!=(const NodeIterator& other) const;

  private:
    explicit NodeIterator(Node* current_node);
    explicit NodeIterator(std::queue<Node*> nodes_queue);

    void advance();

  private:
    std::queue<Node*> m_nodes_queue;
  };

  class ConstNodeIterator
  {
    friend class Node;

  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = std::unique_ptr<Node>;
    using pointer           = const Node*;
    using reference         = const Node&;

  public:
    ~ConstNodeIterator();

    ConstNodeIterator(const ConstNodeIterator&) = default;
    ConstNodeIterator(ConstNodeIterator&&) = default;

    ConstNodeIterator& operator=(const ConstNodeIterator&) = default;
    ConstNodeIterator& operator=(ConstNodeIterator&&) = default;

    reference operator*() const;
    pointer operator->();

    ConstNodeIterator& operator++();
    ConstNodeIterator operator++(int); // NOLINT(cert-dcl21-cpp)

    [[nodiscard]] bool operator==(const ConstNodeIterator& other) const;
    [[nodiscard]] bool operator!=(const ConstNodeIterator& other) const;

  private:
    explicit ConstNodeIterator(const Node* current_node);
    explicit ConstNodeIterator(std::queue<const Node*> nodes_queue);

    void advance();

  private:
    std::queue<const Node*> m_nodes_queue;
  };

} // namespace egnim::scene

#endif //NODE_ITERATOR_H
