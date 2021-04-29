/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/window_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events {

/* --------------------------- WindowGainedFocusEvent ----------------------- */

WindowGainedFocusEvent::WindowGainedFocusEvent() :
  Event(Type::Window)
{

}

WindowGainedFocusEvent::~WindowGainedFocusEvent() = default;

/* ---------------------------- WindowLostFocusEvent ------------------------ */

WindowLostFocusEvent::WindowLostFocusEvent() :
  Event(Type::Window)
{

}

WindowLostFocusEvent::~WindowLostFocusEvent() = default;

/* ------------------------------ WindowCloseEvent -------------------------- */

WindowCloseEvent::WindowCloseEvent() :
  Event(Type::Window)
{

}

WindowCloseEvent::~WindowCloseEvent() = default;

/* ------------------------------ WindowResizeEvent ------------------------- */

WindowResizeEvent::WindowResizeEvent(const sf::Vector2u& size) :
  Event(Type::Window),
  m_size(size)
{

}

WindowResizeEvent::~WindowResizeEvent() = default;

void WindowResizeEvent::setSize(const sf::Vector2u& size)
{
  m_size = size;
}

const sf::Vector2u& WindowResizeEvent::getSize() const
{
  return m_size;
}

} // namespace egnim::events

