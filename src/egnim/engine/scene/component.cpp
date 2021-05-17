/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/component.h>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* -------------------------------------------------------------------------- */

namespace egnim::scene {

Component::Component() :
  m_owner(nullptr)
{

}

Component::~Component() = default;

void Component::setOwner(Node* owner)
{
  assert(!m_owner);
  m_owner = owner;
}

void Component::initializeClone(Component& component) const
{
  component.m_owner = nullptr;
}

Node* Component::getOwner()
{
  return m_owner;
}

const Node* Component::getOwner() const
{
  return m_owner;
}

void Component::onEnter() {}

void Component::onExit() {}

} // namespace egnim::scene