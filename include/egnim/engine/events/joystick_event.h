#ifndef JOYSTICK_EVENT_H
#define JOYSTICK_EVENT_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Window/Joystick.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/events/event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events
{

  class EGNIM_UTILITY_API JoystickEvent: public Event
  {
    EGNIM_CLASS(JoystickEvent, Event)

  public:
    ~JoystickEvent() override;

    void setJoystickId(unsigned joystick_id);
    [[nodiscard]] unsigned getJoystickId() const;

  protected:
    explicit JoystickEvent(unsigned joystick_id);

  private:
    unsigned m_joystick_id;
  };

  class EGNIM_UTILITY_API JoystickConnectedEvent: public JoystickEvent
  {
    EGNIM_CLASS(JoystickConnectedEvent, JoystickEvent)

  public:
    explicit JoystickConnectedEvent(unsigned joystick_id);
    ~JoystickConnectedEvent() override;
  };

  class EGNIM_UTILITY_API JoystickDisconnectedEvent: public JoystickEvent
  {
  EGNIM_CLASS(JoystickDisconnectedEvent, JoystickEvent)

  public:
    explicit JoystickDisconnectedEvent(unsigned joystick_id);
    ~JoystickDisconnectedEvent() override;
  };

  class EGNIM_UTILITY_API JoystickMoveEvent: public JoystickEvent
  {
    EGNIM_CLASS(JoystickMoveEvent, JoystickEvent)

  public:
    explicit JoystickMoveEvent(unsigned joystick_id, sf::Joystick::Axis axis, float position);
    ~JoystickMoveEvent() override;

    void setAxis(sf::Joystick::Axis axis);
    [[nodiscard]] sf::Joystick::Axis getJAxis() const;

    void setPosition(float position);
    [[nodiscard]] float getPosition() const;

  private:
    sf::Joystick::Axis m_axis;
    float m_position;
  };

  class EGNIM_UTILITY_API JoystickButtonPressedEvent: public JoystickEvent
  {
    EGNIM_CLASS(JoystickButtonPressedEvent, JoystickEvent)

  public:
    explicit JoystickButtonPressedEvent(unsigned joystick_id, unsigned button);
    ~JoystickButtonPressedEvent() override;

    void setButton(unsigned button);
    [[nodiscard]] unsigned getButton() const;

  private:
    unsigned m_button;
  };

  class EGNIM_UTILITY_API JoystickButtonReleasedEvent: public JoystickEvent
  {
    EGNIM_CLASS(JoystickButtonReleasedEvent, JoystickEvent)

  public:
    explicit JoystickButtonReleasedEvent(unsigned joystick_id, unsigned button);
    ~JoystickButtonReleasedEvent() override;

    void setButton(unsigned button);
    [[nodiscard]] unsigned getButton() const;

  private:
    unsigned m_button;
  };

} // namespace egnim::events

#endif //JOYSTICK_EVENT_H
