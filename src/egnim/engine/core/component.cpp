/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/component.h>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* -------------------------------------------------------------------------- */

namespace egnim::core {

Component::Component() :
  m_owner(nullptr)
{

}

Component::~Component() = default;

void Component::setOwner(Node* owner)
{
  assert(m_owner);
  m_owner = owner;
}

Node* Component::getOwner()
{
  return m_owner;
}

} // namespace egnim::core