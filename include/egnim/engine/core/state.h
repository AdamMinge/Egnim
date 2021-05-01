#ifndef STATE_H
#define STATE_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <string_view>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{
  class Context;
  class StateStack;

  class EGNIM_UTILITY_API State : private sf::NonCopyable
  {
  public:
    explicit State(StateStack& state_stack, Context& context);
    virtual ~State();

    virtual void draw() = 0;
    virtual void update(sf::Time dt) = 0;

    virtual void onActive();
    virtual void onInactive();
    virtual void onCreate();
    virtual void onDestroy();

  protected:
    void requestStackPush(std::string_view state_id);
    void requestStackPop();
    void requestStateClear();

    [[nodiscard]] Context& getContext();
    [[nodiscard]] const Context& getContext() const;

    [[nodiscard]] StateStack& getStateStack();
    [[nodiscard]] const StateStack& getStateStack() const;

  private:
    Context& m_context;
    StateStack& m_state_stack;
  };

} // namespace egnim::core


#endif //STATE_H
