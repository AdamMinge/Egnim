/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/graphics/group_layer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics {

std::list<const Tileset*>& operator|=(std::list<const Tileset*>& united, const std::list<const Tileset*>& other)
{
  for (auto& layer : other)
    if(std::find(united.begin(), united.end(), layer) == united.end()) united.push_back(layer);
  return united;
}

GroupLayer::GroupLayer() :
  Layer(Type::GroupLayer)
{

}

GroupLayer::~GroupLayer() = default;

void GroupLayer::attachLayer(std::unique_ptr<Layer> layer)
{
  assert(layer);

  layer->setParent(this);
  m_layers.push_back(std::move(layer));
}

std::unique_ptr<Layer> GroupLayer::detachLayer(const Layer& layer)
{
  auto found = std::find_if(m_layers.begin(), m_layers.end(), [&layer](auto &current_layer)
  {
    return current_layer.get() == std::addressof(layer);
  });

  if (found == m_layers.end())
    return nullptr;

  auto found_layer = std::move(*found);
  found_layer->setParent(nullptr);
  m_layers.erase(found);
  return found_layer;
}

const std::list<std::unique_ptr<Layer>>& GroupLayer::getLayers() const
{
  return m_layers;
}

bool GroupLayer::isEmpty() const
{
  return std::all_of(m_layers.begin(), m_layers.end(), [](auto& layer) {
    return layer->isEmpty();
  });
}

std::list<const Tileset*> GroupLayer::getUsedTilesets() const
{
  std::list<const Tileset*> used_tilesets;
  std::for_each(m_layers.begin(), m_layers.end(), [&used_tilesets](auto& layer) {
    used_tilesets |= layer->getUsedTilesets();
  });

  return used_tilesets;
}

bool GroupLayer::isUsedTileset(const Tileset& tileset) const
{
  return std::any_of(m_layers.begin(), m_layers.end(), [&tileset](auto& layer) {
    return layer->isUsedTileset(tileset);
  });
}

bool GroupLayer::canMerge(const Layer& layer) const
{
  return false;
}

bool GroupLayer::merge(const sf::Vector2u& point, const Layer& layer)
{
  return false;
}

GroupLayerIterator GroupLayer::begin()
{
  return GroupLayerIterator(this);
}

ConstGroupLayerIterator GroupLayer::begin() const
{
  return ConstGroupLayerIterator(this);
}

GroupLayerIterator GroupLayer::end()
{
  return GroupLayerIterator(nullptr);
}

ConstGroupLayerIterator GroupLayer::end() const
{
  return ConstGroupLayerIterator(nullptr);
}

std::unique_ptr<Layer> GroupLayer::clone() const
{
  auto clone_layer = std::make_unique<GroupLayer>();
  Layer::initializeClone(*clone_layer);

  for(auto& layer : m_layers)
    clone_layer->attachLayer(layer->clone());

  return clone_layer;
}

} // namespace egnim::graphics