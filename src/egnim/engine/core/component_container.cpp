/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/component_container.h>
#include <egnim/engine/core/component.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core {

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
  component->setOwner(&m_owner);
  m_components.push_back(std::move(component));
}

std::unique_ptr<Component> ComponentContainer::remove(const Component& component)
{
  auto found = std::find_if(m_components.begin(), m_components.end(), [&component](auto& comp){
    return comp.get() == &component;
  });

  if(found == m_components.end())
    return nullptr;

  auto comp = std::move(*found);
  comp->setOwner(nullptr);
  m_components.erase(found);
  return comp;
}

bool ComponentContainer::empty() const
{
  return m_components.empty();
}

size_t ComponentContainer::size() const
{
  return m_components.size();
}


} // namespace egnim::core