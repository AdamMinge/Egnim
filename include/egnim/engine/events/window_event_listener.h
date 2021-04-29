#ifndef WINDOW_EVENT_LISTENER_H
#define WINDOW_EVENT_LISTENER_H

/* --------------------------------- Standard ------------------------------- */
#include <functional>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/events/event_listener.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events
{

  class WindowGainedFocusEvent;
  class WindowLostFocusEvent;
  class WindowCloseEvent;
  class WindowResizeEvent;

  class EGNIM_UTILITY_API WindowEventListener: public EventListener
  {
    EGNIM_CLASS(WindowEventListener, EventListener)

  public:
    using WindowGainedFocusEventCallback = std::function<void(const WindowGainedFocusEvent&)>;
    using WindowLostFocusEventCallback = std::function<void(const WindowLostFocusEvent&)>;
    using WindowCloseEventCallback = std::function<void(const WindowCloseEvent&)>;
    using WindowResizeEventCallback = std::function<void(const WindowResizeEvent&)>;

  public:
    explicit WindowEventListener();
    ~WindowEventListener() override;

    void setWindowGainedFocusEventCallback(const WindowGainedFocusEventCallback& callback);
    void setWindowLostFocusEventCallback(const WindowLostFocusEventCallback& callback);
    void setWindowCloseEventCallbackCallback(const WindowCloseEventCallback& callback);
    void setWindowResizeEventCallbackCallback(const WindowResizeEventCallback& callback);

  protected:
    void invoke(const Event& event) override;

  private:
    WindowGainedFocusEventCallback m_window_gained_focus_event_callback;
    WindowLostFocusEventCallback m_window_lost_focus_event_callback;
    WindowCloseEventCallback m_window_close_event_callback;
    WindowResizeEventCallback m_window_resize_event_callback;
  };

} // namespace egnim::events

#endif //WINDOW_EVENT_LISTENER_H
