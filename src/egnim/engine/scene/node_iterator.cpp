/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/node_iterator.h>
#include <egnim/engine/scene/node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene {

/* -------------------------------- NodeIterator ---------------------------- */

NodeIterator::NodeIterator(Node* current_node)
{
  if(current_node)
    m_nodes_queue.push(current_node);
}

NodeIterator::NodeIterator(std::queue<Node*> nodes_queue) :
  m_nodes_queue(std::move(nodes_queue))
{

}

NodeIterator::~NodeIterator() = default;

NodeIterator::reference NodeIterator::operator*() const
{
  assert(!m_nodes_queue.empty());
  return *m_nodes_queue.front();
}

NodeIterator::pointer NodeIterator::operator->()
{
  assert(!m_nodes_queue.empty());
  return m_nodes_queue.front();
}

NodeIterator& NodeIterator::operator++()
{
  advance();
  return *this;
}

NodeIterator NodeIterator::operator++(int) // NOLINT(cert-dcl21-cpp)
{
  auto iter = *this;
  iter.advance();
  return iter;
}

bool NodeIterator::operator==(const NodeIterator& other) const
{
  auto this_iter_node = m_nodes_queue.empty() ? nullptr : m_nodes_queue.front();
  auto other_iter_node = other.m_nodes_queue.empty() ? nullptr : other.m_nodes_queue.front();

  return this_iter_node == other_iter_node;
}

bool NodeIterator::operator!=(const NodeIterator& other) const
{
  auto this_iter_node = m_nodes_queue.empty() ? nullptr : m_nodes_queue.front();
  auto other_iter_node = other.m_nodes_queue.empty() ? nullptr : other.m_nodes_queue.front();

  return this_iter_node != other_iter_node;
}

void NodeIterator::advance()
{
  assert(!m_nodes_queue.empty());
  auto current_node = m_nodes_queue.front();
  m_nodes_queue.pop();

  for(auto& node : current_node->getChildren())
    m_nodes_queue.push(node.get());
}

/* ------------------------------- ConstNodeIterator ------------------------ */

ConstNodeIterator::ConstNodeIterator(const Node* current_node)
{
  if(current_node)
    m_nodes_queue.push(current_node);
}

ConstNodeIterator::ConstNodeIterator(std::queue<const Node*> nodes_queue)
{
  m_nodes_queue = std::move(nodes_queue);
}

ConstNodeIterator::~ConstNodeIterator() = default;

ConstNodeIterator::reference ConstNodeIterator::operator*() const
{
  assert(!m_nodes_queue.empty());
  return *m_nodes_queue.front();
}

ConstNodeIterator::pointer ConstNodeIterator::operator->()
{
  assert(!m_nodes_queue.empty());
  return m_nodes_queue.front();
}

ConstNodeIterator& ConstNodeIterator::operator++()
{
  advance();
  return *this;
}

ConstNodeIterator ConstNodeIterator::operator++(int) // NOLINT(cert-dcl21-cpp)
{
  auto iter = *this;
  iter.advance();
  return iter;
}

bool ConstNodeIterator::operator==(const ConstNodeIterator& other) const
{
  auto this_iter_node = m_nodes_queue.empty() ? nullptr : m_nodes_queue.front();
  auto other_iter_node = other.m_nodes_queue.empty() ? nullptr : other.m_nodes_queue.front();

  return this_iter_node == other_iter_node;
}

bool ConstNodeIterator::operator!=(const ConstNodeIterator& other) const
{
  auto this_iter_node = m_nodes_queue.empty() ? nullptr : m_nodes_queue.front();
  auto other_iter_node = other.m_nodes_queue.empty() ? nullptr : other.m_nodes_queue.front();

  return this_iter_node != other_iter_node;
}

void ConstNodeIterator::advance()
{
  assert(!m_nodes_queue.empty());
  auto current_node = m_nodes_queue.front();
  m_nodes_queue.pop();

  for(auto& node : current_node->getChildren())
    m_nodes_queue.push(node.get());
}

} // namespace egnim::scene

