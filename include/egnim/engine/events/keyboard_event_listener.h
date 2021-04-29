#ifndef KEYBOARD_EVENT_LISTENER_H
#define KEYBOARD_EVENT_LISTENER_H

/* --------------------------------- Standard ------------------------------- */
#include <functional>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/events/event_listener.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events
{

  class KeyboardKeyPressedEvent;
  class KeyboardKeyReleasedEvent;

  class EGNIM_UTILITY_API KeyboardEventListener: public EventListener
  {
    EGNIM_CLASS(KeyboardEventListener, EventListener)

  public:
    using KeyboardKeyPressedEventCallback = std::function<void(const KeyboardKeyPressedEvent&)>;
    using KeyboardKeyReleasedEventCallback = std::function<void(const KeyboardKeyReleasedEvent&)>;

  public:
    explicit KeyboardEventListener();
    ~KeyboardEventListener() override;

    void setKeyboardKeyPressedEventCallback(const KeyboardKeyPressedEventCallback& callback);
    void setKeyboardKeyReleasedEventCallback(const KeyboardKeyReleasedEventCallback& callback);

  protected:
    void invoke(const Event& event) override;

  private:
    KeyboardKeyPressedEventCallback m_keyboard_key_pressed_event_callback;
    KeyboardKeyReleasedEventCallback m_keyboard_key_released_event_callback;
  };

} // namespace egnim::events

#endif //KEYBOARD_EVENT_LISTENER_H
