#ifndef COMPONENT_CONTANER_H
#define COMPONENT_CONTANER_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Time.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <vector>
#include <memory>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{
  class Node;
  class Component;

  class ComponentContainer
  {
  public:
    explicit ComponentContainer(Node& owner);
    ~ComponentContainer();

    void update(sf::Time dt);

    void add(std::unique_ptr<Component> component);
    std::unique_ptr<Component> remove(const Component& component);

    [[nodiscard]] bool empty() const;
    [[nodiscard]] size_t size() const;

  private:
    std::vector<std::unique_ptr<Component>> m_components;
    Node& m_owner;
  };

} // namespace egnim::core

#endif //COMPONENT_CONTANER_H
