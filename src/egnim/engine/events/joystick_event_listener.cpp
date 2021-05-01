/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/joystick_event_listener.h>
#include <egnim/engine/events/joystick_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events {

JoystickEventListener::JoystickEventListener() :
  EventListener(static_cast<int32_t>(Event::Type::Joystick))
{

}

JoystickEventListener::~JoystickEventListener() = default;

void JoystickEventListener::setJoystickConnectedEventCallback(const JoystickConnectedEventCallback& callback)
{
  m_joystick_connected_event_callback = callback;
}

void JoystickEventListener::setJoystickDisconnectedEventCallback(const JoystickDisconnectedEventCallback& callback)
{
  m_joystick_disconnected_event_callback = callback;
}

void JoystickEventListener::setJoystickMoveEventCallback(const JoystickMoveEventCallback& callback)
{
  m_joystick_move_event_callback = callback;
}

void JoystickEventListener::setJoystickButtonPressedEventCallback(const JoystickButtonPressedEventCallback& callback)
{
  m_joystick_button_pressed_event_callback = callback;
}

void JoystickEventListener::setJoystickButtonReleasedEventCallback(const JoystickButtonReleasedEventCallback& callback)
{
  m_joystick_button_released_event_callback = callback;
}

void JoystickEventListener::invoke(const Event& event)
{
  invokeIfCasted(event,
                 m_joystick_connected_event_callback,
                 m_joystick_disconnected_event_callback,
                 m_joystick_move_event_callback,
                 m_joystick_button_pressed_event_callback,
                 m_joystick_button_released_event_callback);
}

} // namespace egnim::events


