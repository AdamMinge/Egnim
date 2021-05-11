/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/actions/action.h>
/* -------------------------------------------------------------------------- */

namespace egnim::actions {

Action::Action() :
  m_target(nullptr)
{

}

Action::~Action() = default;

void Action::setTarget(scene::Node* target)
{
  m_target = target;
}

scene::Node* Action::getTarget() const
{
  return m_target;
}

void Action::update(sf::Time dt) {}

bool Action::isDone() const
{
  return true;
}

std::unique_ptr<Action> Action::getReverse() const
{
  return nullptr;
}

bool Action::isReversible() const
{
  return false;
}

void Action::initializeClone(Action& action) const
{
  action.m_target = nullptr;
}

} // namespace egnim::actions