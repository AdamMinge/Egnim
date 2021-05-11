#ifndef ACTION_MANAGER_H
#define ACTION_MANAGER_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Time.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <vector>
#include <memory>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{
  class Node;
}

namespace egnim::actions
{

  class Action;

  class EGNIM_UTILITY_API ActionManager
  {
  public:
    explicit ActionManager(scene::Node& owner);
    ~ActionManager();

    void attachAction(std::unique_ptr<Action> action);
    std::unique_ptr<Action> detachAction(const Action& action);
    [[nodiscard]] const std::vector<std::unique_ptr<Action>>& getActions() const;

    void update(sf::Time dt);

    void setEnabled(bool enabled = true);
    [[nodiscard]] bool isEnabled() const;

  private:
    scene::Node& m_owner;
    std::vector<std::unique_ptr<Action>> m_actions;
    bool m_enabled;
  };

} // namespace egnim::actions

#endif //ACTION_MANAGER_H
