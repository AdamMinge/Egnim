/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/mouse_event_listener.h>
#include <egnim/engine/events/mouse_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events {

MouseEventListener::MouseEventListener() :
  EventListener(static_cast<int32_t>(Event::Type::Mouse))
{

}

MouseEventListener::~MouseEventListener() = default;

void MouseEventListener::setMouseMoveEventCallback(const MouseMoveEventCallback& callback)
{
  m_mouse_move_event_event_callback = callback;
}

void MouseEventListener::setMouseButtonPressedEventCallback(const MouseButtonPressedEventCallback& callback)
{
  m_mouse_button_pressed_event_callback = callback;
}

void MouseEventListener::setMouseButtonReleasedEventCallback(const MouseButtonReleasedEventCallback& callback)
{
  m_mouse_button_released_event_callback = callback;
}

void MouseEventListener::setMouseWheelScrollEventCallback(const MouseWheelScrollEventCallback& callback)
{
  m_mouse_wheel_scroll_event_callback = callback;
}

void MouseEventListener::invoke(const Event& event)
{
  invokeIfCasted(event,
                 m_mouse_move_event_event_callback,
                 m_mouse_button_pressed_event_callback,
                 m_mouse_button_released_event_callback,
                 m_mouse_wheel_scroll_event_callback);
}

} // namespace egnim::events