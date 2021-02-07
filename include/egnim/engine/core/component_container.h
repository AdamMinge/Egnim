#ifndef COMPONENT_CONTANER_H
#define COMPONENT_CONTANER_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Time.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <vector>
#include <memory>
/* -------------------------------------------------------------------------- */

namespace core
{
  class SceneNode;
  class Component;

  class ComponentContainer
  {
  public:
    explicit ComponentContainer(SceneNode& owner);
    ~ComponentContainer();

    void update(sf::Time dt);

    void add(std::unique_ptr<Component> component);
    std::unique_ptr<Component> remove(const Component& component);

    [[nodiscard]] bool empty() const;
    [[nodiscard]] size_t size() const;

  private:
    std::vector<std::unique_ptr<Component>> m_components;
    SceneNode& m_owner;
  };

} // namespace core

#endif //COMPONENT_CONTANER_H
