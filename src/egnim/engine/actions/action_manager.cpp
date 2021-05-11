/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/actions/action_manager.h>
#include <egnim/engine/actions/action.h>
/* -------------------------------------------------------------------------- */

namespace egnim::actions {

ActionManager::ActionManager(scene::Node& owner) :
  m_owner(owner),
  m_enabled(true)
{

}

ActionManager::~ActionManager() = default;

void ActionManager::attachAction(std::unique_ptr<Action> action)
{
  action->setTarget(std::addressof(m_owner));
  m_actions.push_back(std::move(action));
}

std::unique_ptr<Action> ActionManager::detachAction(const Action& action)
{
  auto found = std::find_if(m_actions.begin(), m_actions.end(), [&action](auto &current_action)
  {
    return current_action.get() == std::addressof(action);
  });

  if (found == m_actions.end())
    return nullptr;

  auto found_action = std::move(*found);
  found_action->setTarget(nullptr);
  m_actions.erase(found);
  return found_action;
}

const std::vector<std::unique_ptr<Action>>& ActionManager::getActions() const
{
  return m_actions;
}

void ActionManager::update(sf::Time dt)
{
  if(!isEnabled())
    return;

  for(auto& action : m_actions)
    action->update(dt);

  m_actions.erase(std::remove_if(m_actions.begin(), m_actions.end(), [](auto&& action){
    return action->isDone();
  }), m_actions.end());
}

void ActionManager::setEnabled(bool enabled)
{
  m_enabled = enabled;
}

bool ActionManager::isEnabled() const
{
  return m_enabled;
}

} // namespace egnim::actions