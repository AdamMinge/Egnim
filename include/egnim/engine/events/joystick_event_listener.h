#ifndef JOYSTICK_EVENT_LISTENER_H
#define JOYSTICK_EVENT_LISTENER_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Window/Joystick.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/events/event_listener.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events
{

  class JoystickConnectedEvent;
  class JoystickDisconnectedEvent;
  class JoystickMoveEvent;
  class JoystickButtonPressedEvent;
  class JoystickButtonReleasedEvent;

  class EGNIM_UTILITY_API JoystickEventListener: public EventListener
  {
    EGNIM_CLASS(JoystickEventListener, EventListener)

  public:
    using JoystickConnectedEventCallback = std::function<void(const JoystickConnectedEvent&)>;
    using JoystickDisconnectedEventCallback = std::function<void(const JoystickDisconnectedEvent&)>;
    using JoystickMoveEventCallback = std::function<void(const JoystickMoveEvent&)>;
    using JoystickButtonPressedEventCallback = std::function<void(const JoystickButtonPressedEvent&)>;
    using JoystickButtonReleasedEventCallback = std::function<void(const JoystickButtonReleasedEvent&)>;

  public:
    explicit JoystickEventListener();
    ~JoystickEventListener() override;

    void setJoystickConnectedEventCallback(const JoystickConnectedEventCallback& callback);
    void setJoystickDisconnectedEventCallback(const JoystickDisconnectedEventCallback& callback);
    void setJoystickMoveEventCallback(const JoystickMoveEventCallback& callback);
    void setJoystickButtonPressedEventCallback(const JoystickButtonPressedEventCallback& callback);
    void setJoystickButtonReleasedEventCallback(const JoystickButtonReleasedEventCallback& callback);

  protected:
    void invoke(const Event& event) override;

  private:
    JoystickConnectedEventCallback m_joystick_connected_event_callback;
    JoystickDisconnectedEventCallback m_joystick_disconnected_event_callback;
    JoystickMoveEventCallback m_joystick_move_event_callback;
    JoystickButtonPressedEventCallback m_joystick_button_pressed_event_callback;
    JoystickButtonReleasedEventCallback m_joystick_button_released_event_callback;
  };

} // namespace egnim::events

#endif //JOYSTICK_EVENT_LISTENER_H
