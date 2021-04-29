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
  class MouseKeyPressedEvent;
  class MouseKeyReleasedEvent;
  class MouseWheelScrollEvent;

  class EGNIM_UTILITY_API MouseEventListener: public EventListener
  {
  EGNIM_CLASS(MouseEventListener, EventListener)

  public:
    using MouseMoveEventCallback = std::function<void(const MouseMoveEvent&)>;
    using MouseKeyPressedEventCallback = std::function<void(const MouseKeyPressedEvent&)>;
    using MouseKeyReleasedEventCallback = std::function<void(const MouseKeyReleasedEvent&)>;
    using MouseWheelScrollEventCallback = std::function<void(const MouseWheelScrollEvent&)>;

  public:
    explicit MouseEventListener();
    ~MouseEventListener() override;

    void setMouseMoveEventCallback(const MouseMoveEventCallback& callback);
    void setMouseKeyPressedEventCallback(const MouseKeyPressedEventCallback& callback);
    void setMouseKeyReleasedEventCallback(const MouseKeyReleasedEventCallback& callback);
    void setMouseWheelScrollEventCallback(const MouseWheelScrollEventCallback& callback);

  protected:
    void invoke(const Event& event) override;

  private:
    MouseMoveEventCallback m_mouse_move_event_event_callback;
    MouseKeyPressedEventCallback m_mouse_key_pressed_event_callback;
    MouseKeyReleasedEventCallback m_mouse_key_released_event_callback;
    MouseWheelScrollEventCallback m_mouse_wheel_scroll_event_callback;
  };

} // namespace egnim::events

#endif //MOUSE_EVENT_LISTENER_H
