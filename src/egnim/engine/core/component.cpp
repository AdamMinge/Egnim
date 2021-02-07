/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/component.h>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* -------------------------------------------------------------------------- */

namespace core {

Component::Component() :
  m_owner(nullptr)
{

}

Component::~Component() = default;

void Component::setOwner(SceneNode* owner)
{
  assert(m_owner);
  m_owner = owner;
}

SceneNode* Component::getOwner()
{
  return m_owner;
}

} // namespace core