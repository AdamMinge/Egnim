/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/mouse_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events {

/* --------------------------------- MouseEvent ----------------------------- */

MouseEvent::MouseEvent(const sf::Vector2i& position)  :
  Event(Type::Mouse),
  m_position(position)
{

}

MouseEvent::~MouseEvent() = default;

void MouseEvent::setPosition(const sf::Vector2i& position)
{
  m_position = position;
}

const sf::Vector2i& MouseEvent::getPosition() const
{
  return m_position;
}


/* -------------------------------- MouseMoveEvent -------------------------- */

MouseMoveEvent::MouseMoveEvent(const sf::Vector2i& position) :
  MouseEvent(position)
{

}

MouseMoveEvent::~MouseMoveEvent() = default;

/* ---------------------------- MouseKeyPressedEvent ------------------------ */

MouseKeyPressedEvent::MouseKeyPressedEvent(sf::Mouse::Button button, const sf::Vector2i& position) :
  MouseEvent(position),
  m_button(button)
{

}

MouseKeyPressedEvent::~MouseKeyPressedEvent() = default;

void MouseKeyPressedEvent::setButton(sf::Mouse::Button button)
{
  m_button = button;
}

sf::Mouse::Button MouseKeyPressedEvent::getButton() const
{
  return m_button;
}

/* --------------------------- MouseKeyReleasedEvent ------------------------ */

MouseKeyReleasedEvent::MouseKeyReleasedEvent(sf::Mouse::Button button, const sf::Vector2i& position) :
  MouseEvent(position),
  m_button(button)
{

}

MouseKeyReleasedEvent::~MouseKeyReleasedEvent() = default;

void MouseKeyReleasedEvent::setButton(sf::Mouse::Button button)
{
  m_button = button;
}

sf::Mouse::Button MouseKeyReleasedEvent::getButton() const
{
  return m_button;
}

/* ---------------------------- MouseWheelScrollEvent ----------------------- */

MouseWheelScrollEvent::MouseWheelScrollEvent(sf::Mouse::Wheel wheel, float delta, const sf::Vector2i position) :
  MouseEvent(position),
  m_wheel(wheel),
  m_delta(delta)
{

}

MouseWheelScrollEvent::~MouseWheelScrollEvent() = default;

void MouseWheelScrollEvent::setWheel(sf::Mouse::Wheel wheel)
{
  m_wheel = wheel;
}

sf::Mouse::Wheel MouseWheelScrollEvent::getWheel() const
{
  return m_wheel;
}

void MouseWheelScrollEvent::setDelta(float delta)
{
  m_delta = delta;
}

float MouseWheelScrollEvent::getDelta() const
{
  return m_delta;
}

} // namespace egnim::events