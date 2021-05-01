/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/joystick_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events {

/* ------------------------------- JoystickEvent ---------------------------- */

JoystickEvent::JoystickEvent(unsigned joystick_id) :
  Event(Type::Joystick),
  m_joystick_id(joystick_id)
{

}

JoystickEvent::~JoystickEvent() = default;

void JoystickEvent::setJoystickId(unsigned joystick_id)
{
  m_joystick_id = joystick_id;
}

unsigned JoystickEvent::getJoystickId() const
{
  return m_joystick_id;
}

/* --------------------------- JoystickConnectedEvent ------------------------ */

JoystickConnectedEvent::JoystickConnectedEvent(unsigned joystick_id) :
  JoystickEvent(joystick_id)
{

}

JoystickConnectedEvent::~JoystickConnectedEvent() = default;

/* -------------------------- JoystickDisconnectedEvent ---------------------- */

JoystickDisconnectedEvent::JoystickDisconnectedEvent(unsigned joystick_id) :
  JoystickEvent(joystick_id)
{

}

JoystickDisconnectedEvent::~JoystickDisconnectedEvent() = default;

/* ------------------------------ JoystickMoveEvent -------------------------- */

JoystickMoveEvent::JoystickMoveEvent(unsigned joystick_id, sf::Joystick::Axis axis, float position) :
  JoystickEvent(joystick_id),
  m_axis(axis),
  m_position(position)
{

}

JoystickMoveEvent::~JoystickMoveEvent() = default;

void JoystickMoveEvent::setAxis(sf::Joystick::Axis axis)
{
  m_axis = axis;
}

sf::Joystick::Axis JoystickMoveEvent::getJAxis() const
{
  return m_axis;
}

void JoystickMoveEvent::setPosition(float position)
{
  m_position = position;
}

float JoystickMoveEvent::getPosition() const
{
  return m_position;
}

/* -------------------------- JoystickButtonPressedEvent --------------------- */

JoystickButtonPressedEvent::JoystickButtonPressedEvent(unsigned joystick_id, unsigned button) :
  JoystickEvent(joystick_id),
  m_button(button)
{

}

JoystickButtonPressedEvent::~JoystickButtonPressedEvent() = default;

void JoystickButtonPressedEvent::setButton(unsigned button)
{
  m_button = button;
}

unsigned JoystickButtonPressedEvent::getButton() const
{
  return m_button;
}

/* -------------------------- JoystickButtonReleasedEvent -------------------- */

JoystickButtonReleasedEvent::JoystickButtonReleasedEvent(unsigned joystick_id, unsigned button) :
  JoystickEvent(joystick_id),
  m_button(button)
{

}

JoystickButtonReleasedEvent::~JoystickButtonReleasedEvent() = default;

void JoystickButtonReleasedEvent::setButton(unsigned button)
{
  m_button = button;
}

unsigned JoystickButtonReleasedEvent::getButton() const
{
  return m_button;
}


} // namespace egnim::events
