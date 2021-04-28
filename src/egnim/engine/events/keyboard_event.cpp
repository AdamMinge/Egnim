/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/keyboard_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events {

/* ------------------------------- KeyboardEvent ---------------------------- */

KeyboardEvent::KeyboardEvent(sf::Keyboard::Key key) :
  Event(Type::Keyboard),
  m_key(key),
  m_alt(false),
  m_control(false),
  m_shift(false),
  m_system(false)
{

}

KeyboardEvent::~KeyboardEvent() = default;

void KeyboardEvent::setKey(sf::Keyboard::Key key)
{
  m_key = key;
}

sf::Keyboard::Key KeyboardEvent::getKey() const
{
  return m_key;
}

void KeyboardEvent::setAltPressed(bool pressed)
{
  m_alt = pressed;
}

void KeyboardEvent::setControlPressed(bool pressed)
{
  m_control = pressed;
}

void KeyboardEvent::setShiftPressed(bool pressed)
{
  m_shift = pressed;
}

void KeyboardEvent::setSystemPressed(bool pressed)
{
  m_system = pressed;
}

bool KeyboardEvent::isAltPressed() const
{
  return m_alt;
}

bool KeyboardEvent::isControlPressed() const
{
  return m_control;
}

bool KeyboardEvent::isShiftPressed() const
{
  return m_shift;
}

bool KeyboardEvent::isSystemPressed() const
{
  return m_system;
}

/* ------------------------------ KeyPressedEvent --------------------------- */

KeyPressedEvent::KeyPressedEvent(sf::Keyboard::Key key) :
  KeyboardEvent(key)
{

}

KeyPressedEvent::~KeyPressedEvent() = default;

/* ------------------------------ KeyReleasedEvent -------------------------- */

KeyReleasedEvent::KeyReleasedEvent(sf::Keyboard::Key key) :
  KeyboardEvent(key)
{

}

KeyReleasedEvent::~KeyReleasedEvent() = default;

} // namespace egnim::events