#ifndef COMPONENT_H
#define COMPONENT_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Time.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{
  class Node;
  class ComponentContainer;

  class EGNIM_UTILITY_API Component
  {
    friend ComponentContainer;

  public:
    explicit Component();
    virtual ~Component();

    virtual void update(sf::Time dt);

    [[nodiscard]] Node* getOwner();
    [[nodiscard]] const Node* getOwner() const;

  protected:
    void setOwner(Node* owner);

    virtual void onEnter();
    virtual void onExit();

  private:
    Node* m_owner;
  };

} // namespace egnim::scene

#endif //COMPONENT_H
