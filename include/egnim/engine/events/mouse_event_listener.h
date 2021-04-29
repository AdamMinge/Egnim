#ifndef MOUSE_EVENT_LISTENER_H
#define MOUSE_EVENT_LISTENER_H

/* --------------------------------- Standard ------------------------------- */
#include <functional>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/events/event_listener.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events
{

  class MouseMoveEvent;
  class MouseButtonPressedEvent;
  class MouseButtonReleasedEvent;
  class MouseWheelScrollEvent;

  class EGNIM_UTILITY_API MouseEventListener: public EventListener
  {
  EGNIM_CLASS(MouseEventListener, EventListener)

  public:
    using MouseMoveEventCallback = std::function<void(const MouseMoveEvent&)>;
    using MouseButtonPressedEventCallback = std::function<void(const MouseButtonPressedEvent&)>;
    using MouseButtonReleasedEventCallback = std::function<void(const MouseButtonReleasedEvent&)>;
    using MouseWheelScrollEventCallback = std::function<void(const MouseWheelScrollEvent&)>;

  public:
    explicit MouseEventListener();
    ~MouseEventListener() override;

    void setMouseMoveEventCallback(const MouseMoveEventCallback& callback);
    void setMouseButtonPressedEventCallback(const MouseButtonPressedEventCallback& callback);
    void setMouseButtonReleasedEventCallback(const MouseButtonReleasedEventCallback& callback);
    void setMouseWheelScrollEventCallback(const MouseWheelScrollEventCallback& callback);

  protected:
    void invoke(const Event& event) override;

  private:
    MouseMoveEventCallback m_mouse_move_event_callback;
    MouseButtonPressedEventCallback m_mouse_button_pressed_event_callback;
    MouseButtonReleasedEventCallback m_mouse_button_released_event_callback;
    MouseWheelScrollEventCallback m_mouse_wheel_scroll_event_callback;
  };

} // namespace egnim::events

#endif //MOUSE_EVENT_LISTENER_H
