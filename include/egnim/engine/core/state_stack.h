#ifndef STATE_STACK_H
#define STATE_STACK_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <string_view>
#include <functional>
#include <memory>
#include <queue>
#include <map>
/* -------------------------------------------------------------------------- */

namespace core
{
  class Context;
  class State;

  class StateStack : private sf::NonCopyable
  {
  public:
    explicit StateStack(Context& context);
    ~StateStack();

    void draw();
    void update(sf::Time dt);
    void handleEvent(const sf::Event& event);

    void pushState(std::string_view state_id);
    void popState();
    void clearStates();

    template<typename TYPE, typename ...Args>
    void registerState(std::string_view state_id, Args... args);

  private:
    std::unique_ptr<State> createState(std::string_view state_id);
    void applyPendingChanges();

  private:
    Context& m_context;

    std::vector<std::unique_ptr<State>> m_states;
    std::queue<std::function<void()>> m_pending_changes;
    std::map<std::string_view, std::function<std::unique_ptr<State>()>> m_factories;
  };

  template<typename TYPE, typename ...Args>
  void StateStack::registerState(std::string_view state_id, Args... args)
  {
    m_factories.insert(std::make_pair(state_id, [args...](){
      return std::make_unique<TYPE>(args...);
    }));
  }

} // namespace core

#endif //STATE_STACK_H
