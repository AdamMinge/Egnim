/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/window_event_listener.h>
#include <egnim/engine/events/window_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events {

WindowEventListener::WindowEventListener() :
  EventListener(static_cast<int32_t>(Event::Type::Window))
{

}

WindowEventListener::~WindowEventListener() = default;

void WindowEventListener::setWindowGainedFocusEventCallback(const WindowGainedFocusEventCallback& callback)
{
  m_window_gained_focus_event_callback = callback;
}

void WindowEventListener::setWindowLostFocusEventCallback(const WindowLostFocusEventCallback& callback)
{
  m_window_lost_focus_event_callback = callback;
}

void WindowEventListener::setWindowCloseEventCallbackCallback(const WindowCloseEventCallback& callback)
{
  m_window_close_event_callback = callback;
}

void WindowEventListener::setWindowResizeEventCallbackCallback(const WindowResizeEventCallback& callback)
{
  m_window_resize_event_callback = callback;
}

void WindowEventListener::invoke(const Event& event)
{
  invokeIfCasted(event,
                 m_window_gained_focus_event_callback,
                 m_window_lost_focus_event_callback,
                 m_window_close_event_callback,
                 m_window_resize_event_callback);
}

} // namespace egnim::events



