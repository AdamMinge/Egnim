#ifndef GAME_H
#define GAME_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{
  class StateStack;
  class Context;

  class EGNIM_UTILITY_API Game
  {
  public:
    explicit Game();
    virtual ~Game();

    void setTimePerFrame(const sf::Time& time_per_frame);
    [[nodiscard]] sf::Time getTimePerFrame() const;

    [[nodiscard]] Context& getContext();
    [[nodiscard]] const Context& getContext() const;

    [[nodiscard]] StateStack& getStateStack();
    [[nodiscard]] const StateStack& getStateStack() const;

    void run();

  protected:
    virtual void processInput();
    virtual void update(sf::Time dt);
    virtual void render();

    virtual void processWindowEvent(const sf::Event& window_event);
    virtual void processKeyboardEvent(const sf::Event& keyboard_event);
    virtual void processMouseEvent(const sf::Event& mouse_event);
    virtual void processJoystickEvent(const sf::Event& joystick_event);

  private:
    std::unique_ptr<Context> m_context;
    std::unique_ptr<StateStack> m_states;
    sf::Time m_time_per_frame;
  };

} // namespace egnim::core

#endif //GAME_H
