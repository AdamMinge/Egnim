/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/graphics/group_layer_iterator.h>
#include <egnim/engine/graphics/group_layer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics {

/* --------------------------- GroupLayerIterator --------------------------- */

GroupLayerIterator::GroupLayerIterator(GroupLayer* group_layer)
{
  if(group_layer)
    m_layers_queue.push(group_layer);
}

GroupLayerIterator::GroupLayerIterator(std::queue<Layer*> layers_queue) :
  m_layers_queue(std::move(layers_queue))
{

}

GroupLayerIterator::~GroupLayerIterator() = default;

GroupLayerIterator::reference GroupLayerIterator::operator*() const
{
  assert(!m_layers_queue.empty());
  return *m_layers_queue.front();
}

GroupLayerIterator::pointer GroupLayerIterator::operator->()
{
  assert(!m_layers_queue.empty());
  return m_layers_queue.front();
}

GroupLayerIterator& GroupLayerIterator::operator++()
{
  advance();
  return *this;
}

GroupLayerIterator GroupLayerIterator::operator++(int) // NOLINT(cert-dcl21-cpp)
{
  auto iter = *this;
  iter.advance();
  return iter;
}

bool GroupLayerIterator::operator==(const GroupLayerIterator& other) const
{
  auto this_iter_node = m_layers_queue.empty() ? nullptr : m_layers_queue.front();
  auto other_iter_node = other.m_layers_queue.empty() ? nullptr : other.m_layers_queue.front();

  return this_iter_node == other_iter_node;
}

bool GroupLayerIterator::operator!=(const GroupLayerIterator& other) const
{
  auto this_iter_node = m_layers_queue.empty() ? nullptr : m_layers_queue.front();
  auto other_iter_node = other.m_layers_queue.empty() ? nullptr : other.m_layers_queue.front();

  return this_iter_node != other_iter_node;
}

void GroupLayerIterator::advance()
{
  assert(!m_layers_queue.empty());
  auto current_layer = m_layers_queue.front();
  m_layers_queue.pop();

  if(auto group_layer = dynamic_cast<GroupLayer*>(current_layer); group_layer)
  {
    for(auto& layer : group_layer->getLayers())
      m_layers_queue.push(layer.get());
  }
}

/* ------------------------- ConstGroupLayerIterator ------------------------ */

ConstGroupLayerIterator::ConstGroupLayerIterator(const GroupLayer* group_layer)
{
  if(group_layer)
    m_layers_queue.push(group_layer);
}

ConstGroupLayerIterator::ConstGroupLayerIterator(std::queue<const Layer*> layers_queue) :
  m_layers_queue(std::move(layers_queue))
{

}

ConstGroupLayerIterator::~ConstGroupLayerIterator() = default;

ConstGroupLayerIterator::reference ConstGroupLayerIterator::operator*() const
{
  assert(!m_layers_queue.empty());
  return *m_layers_queue.front();
}

ConstGroupLayerIterator::pointer ConstGroupLayerIterator::operator->()
{
  assert(!m_layers_queue.empty());
  return m_layers_queue.front();
}

ConstGroupLayerIterator& ConstGroupLayerIterator::operator++()
{
  advance();
  return *this;
}

ConstGroupLayerIterator ConstGroupLayerIterator::operator++(int) // NOLINT(cert-dcl21-cpp)
{
  auto iter = *this;
  iter.advance();
  return iter;
}

bool ConstGroupLayerIterator::operator==(const ConstGroupLayerIterator& other) const
{
  auto this_iter_node = m_layers_queue.empty() ? nullptr : m_layers_queue.front();
  auto other_iter_node = other.m_layers_queue.empty() ? nullptr : other.m_layers_queue.front();

  return this_iter_node == other_iter_node;
}

bool ConstGroupLayerIterator::operator!=(const ConstGroupLayerIterator& other) const
{
  auto this_iter_node = m_layers_queue.empty() ? nullptr : m_layers_queue.front();
  auto other_iter_node = other.m_layers_queue.empty() ? nullptr : other.m_layers_queue.front();

  return this_iter_node != other_iter_node;
}

void ConstGroupLayerIterator::advance()
{
  assert(!m_layers_queue.empty());
  auto current_layer = m_layers_queue.front();
  m_layers_queue.pop();

  if(auto group_layer = dynamic_cast<const GroupLayer*>(current_layer); group_layer)
  {
    for(auto& layer : group_layer->getLayers())
      m_layers_queue.push(layer.get());
  }
}

} // namespace egnim::graphics
