/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/component_container.h>
#include <egnim/engine/scene/component.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene {

ComponentContainer::ComponentContainer(Node& owner) :
  m_owner(owner)
{

}

ComponentContainer::~ComponentContainer() = default;

void ComponentContainer::update(sf::Time dt)
{
  for(auto& component : m_components)
    component->update(dt);
}

void ComponentContainer::add(std::unique_ptr<Component> component)
{
  auto& component_ref = *component;
  m_components.push_back(std::move(component));
  component_ref.setOwner(&m_owner);
  component_ref.onEnter();
}

void ComponentContainer::remove(const Component& component)
{
  auto found = std::find_if(m_components.begin(), m_components.end(), [&component](auto& comp){
    return comp.get() == &component;
  });

  if(found == m_components.end())
    return;

  auto comp = std::move(*found);
  m_components.erase(found);
  comp->setOwner(nullptr);
  comp->onExit();
}

std::unique_ptr<Component> ComponentContainer::take(const Component& component)
{
  auto found = std::find_if(m_components.begin(), m_components.end(), [&component](auto& comp){
    return comp.get() == &component;
  });

  if(found == m_components.end())
    return nullptr;

  auto comp = std::move(*found);
  m_components.erase(found);
  comp->setOwner(nullptr);
  return comp;
}

const std::vector<std::unique_ptr<Component>>& ComponentContainer::getComponents() const
{
  return m_components;
}

bool ComponentContainer::empty() const
{
  return m_components.empty();
}

size_t ComponentContainer::size() const
{
  return m_components.size();
}

void ComponentContainer::onEnter()
{
  for(auto& component : m_components)
    component->onEnter();
}

void ComponentContainer::onExit()
{
  for(auto& component : m_components)
    component->onExit();
}


} // namespace egnim::scene