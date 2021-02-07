#ifndef COMPONENT_H
#define COMPONENT_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Time.hpp>
/* -------------------------------------------------------------------------- */

namespace core
{
  class SceneNode;
  class ComponentContainer;

  class Component
  {
    friend ComponentContainer;

  public:
    explicit Component();
    virtual ~Component();

    virtual void update(sf::Time dt) = 0;

  protected:
    void setOwner(SceneNode* owner);
    SceneNode* getOwner();

  private:
    SceneNode* m_owner;
  };

} // namespace core

#endif //COMPONENT_H
