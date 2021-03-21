/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/node_iterator.h>
#include <egnim/engine/scene/node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene {

/* -------------------------------- NodeIterator ---------------------------- */

NodeIterator::NodeIterator(Node* current_node)
{
  m_nodes_queue.push(current_node);
}

NodeIterator::NodeIterator(std::queue<Node*> nodes_queue)
{
  m_nodes_queue = std::move(nodes_queue);
}

NodeIterator::~NodeIterator() = default;

NodeIterator::reference NodeIterator::operator*() const
{
  return *m_nodes_queue.front();
}

NodeIterator::pointer NodeIterator::operator->()
{
  return m_nodes_queue.front();
}

NodeIterator& NodeIterator::operator++()
{
  auto current_node = m_nodes_queue.front();
  m_nodes_queue.pop();

  for(auto& node : current_node->getChildren())
    m_nodes_queue.push(node.get());

  return *this;
}

NodeIterator NodeIterator::operator++(int) // NOLINT(cert-dcl21-cpp)
{
  auto nodes_queue = m_nodes_queue;

  auto current_node = nodes_queue.front();
  nodes_queue.pop();

  for(auto& node : current_node->getChildren())
    nodes_queue.push(node.get());

  return NodeIterator(nodes_queue);
}

bool NodeIterator::operator==(const NodeIterator& other) const
{
  return m_nodes_queue.front() == other.m_nodes_queue.front();
}

bool NodeIterator::operator!=(const NodeIterator& other) const
{
  return m_nodes_queue.front() != other.m_nodes_queue.front();
}

/* ------------------------------- ConstNodeIterator ------------------------ */

ConstNodeIterator::ConstNodeIterator(const Node* current_node)
{
  m_nodes_queue.push(current_node);
}

ConstNodeIterator::ConstNodeIterator(std::queue<const Node*> nodes_queue)
{
  m_nodes_queue = std::move(nodes_queue);
}

ConstNodeIterator::~ConstNodeIterator() = default;

ConstNodeIterator::reference ConstNodeIterator::operator*() const
{
  return *m_nodes_queue.front();
}

ConstNodeIterator::pointer ConstNodeIterator::operator->()
{
  return m_nodes_queue.front();
}

ConstNodeIterator& ConstNodeIterator::operator++()
{
  auto current_node = m_nodes_queue.front();
  m_nodes_queue.pop();

  for(auto& node : current_node->getChildren())
    m_nodes_queue.push(node.get());

  return *this;
}

ConstNodeIterator ConstNodeIterator::operator++(int) // NOLINT(cert-dcl21-cpp)
{
  auto nodes_queue = m_nodes_queue;

  auto current_node = nodes_queue.front();
  nodes_queue.pop();

  for(auto& node : current_node->getChildren())
    nodes_queue.push(node.get());

  return ConstNodeIterator(nodes_queue);
}

bool ConstNodeIterator::operator==(const ConstNodeIterator& other) const
{
  return m_nodes_queue.front() == other.m_nodes_queue.front();
}

bool ConstNodeIterator::operator!=(const ConstNodeIterator& other) const
{
  return m_nodes_queue.front() != other.m_nodes_queue.front();
}


} // namespace egnim::scene

