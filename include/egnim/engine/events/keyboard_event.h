#ifndef KEYBOARD_EVENT_H
#define KEYBOARD_EVENT_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Window/Keyboard.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/events/event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events
{

  class EGNIM_UTILITY_API KeyboardEvent: public Event
  {
    EGNIM_CLASS(KeyboardEvent, Event)

  public:
    ~KeyboardEvent() override;

    void setKey(sf::Keyboard::Key key);
    [[nodiscard]] sf::Keyboard::Key getKey() const;

    void setAltPressed(bool pressed = true);
    void setControlPressed(bool pressed = true);
    void setShiftPressed(bool pressed = true);
    void setSystemPressed(bool pressed = true);

    [[nodiscard]] bool isAltPressed() const;
    [[nodiscard]] bool isControlPressed() const;
    [[nodiscard]] bool isShiftPressed() const;
    [[nodiscard]] bool isSystemPressed() const;

  protected:
    explicit KeyboardEvent(sf::Keyboard::Key key);

  private:
    sf::Keyboard::Key m_key;
    bool m_alt;
    bool m_control;
    bool m_shift;
    bool m_system;
  };

  class EGNIM_UTILITY_API KeyboardKeyPressedEvent: public KeyboardEvent
  {
    EGNIM_CLASS(KeyboardKeyPressedEvent, KeyboardEvent)

  public:
    explicit KeyboardKeyPressedEvent(sf::Keyboard::Key key);
    ~KeyboardKeyPressedEvent() override;
  };

  class EGNIM_UTILITY_API KeyboardKeyReleasedEvent: public KeyboardEvent
  {
  EGNIM_CLASS(KeyboardKeyReleasedEvent, KeyboardEvent)

  public:
    explicit KeyboardKeyReleasedEvent(sf::Keyboard::Key key);
    ~KeyboardKeyReleasedEvent() override;
  };

}; // namespace egnim::events

#endif //KEYBOARD_EVENT_H
