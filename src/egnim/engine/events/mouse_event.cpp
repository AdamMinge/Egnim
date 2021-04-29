/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/mouse_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events {

/* ----------------------------- MousePositionEvent ------------------------- */

MousePositionEvent::MousePositionEvent(const sf::Vector2i& position)  :
  Event(Type::Mouse),
  m_position(position)
{

}

MousePositionEvent::~MousePositionEvent() = default;

void MousePositionEvent::setPosition(const sf::Vector2i& position)
{
  m_position = position;
}

const sf::Vector2i& MousePositionEvent::getPosition() const
{
  return m_position;
}

/* ------------------------------ MouseEnteredEvent ------------------------- */

MouseEnteredEvent::MouseEnteredEvent(const sf::Vector2i& position) :
  MousePositionEvent(position)
{

}

MouseEnteredEvent::~MouseEnteredEvent() = default;

/* -------------------------------- MouseLeftEvent -------------------------- */

MouseLeftEvent::MouseLeftEvent(const sf::Vector2i& position) :
  MousePositionEvent(position)
{

}

MouseLeftEvent::~MouseLeftEvent() = default;

/* -------------------------------- MouseMoveEvent -------------------------- */

MouseMoveEvent::MouseMoveEvent(const sf::Vector2i& position) :
  MousePositionEvent(position)
{

}

MouseMoveEvent::~MouseMoveEvent() = default;

/* --------------------------- MouseButtonPressedEvent ---------------------- */

MouseButtonPressedEvent::MouseButtonPressedEvent(sf::Mouse::Button button, const sf::Vector2i& position) :
  MousePositionEvent(position),
  m_button(button)
{

}

MouseButtonPressedEvent::~MouseButtonPressedEvent() = default;

void MouseButtonPressedEvent::setButton(sf::Mouse::Button button)
{
  m_button = button;
}

sf::Mouse::Button MouseButtonPressedEvent::getButton() const
{
  return m_button;
}

/* -------------------------- MouseButtonReleasedEvent ---------------------- */

MouseButtonReleasedEvent::MouseButtonReleasedEvent(sf::Mouse::Button button, const sf::Vector2i& position) :
  MousePositionEvent(position),
  m_button(button)
{

}

MouseButtonReleasedEvent::~MouseButtonReleasedEvent() = default;

void MouseButtonReleasedEvent::setButton(sf::Mouse::Button button)
{
  m_button = button;
}

sf::Mouse::Button MouseButtonReleasedEvent::getButton() const
{
  return m_button;
}

/* ---------------------------- MouseWheelScrollEvent ----------------------- */

MouseWheelScrollEvent::MouseWheelScrollEvent(sf::Mouse::Wheel wheel, float delta, const sf::Vector2i& position) :
  MousePositionEvent(position),
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