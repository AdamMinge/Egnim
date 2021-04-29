/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/keyboard_event_listener.h>
#include <egnim/engine/events/keyboard_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events {

KeyboardEventListener::KeyboardEventListener() :
  EventListener(static_cast<int32_t>(Event::Type::Keyboard))
{

}

KeyboardEventListener::~KeyboardEventListener() = default;

void KeyboardEventListener::setKeyboardKeyPressedEventCallback(const KeyboardKeyPressedEventCallback & callback)
{
  m_keyboard_key_pressed_event_callback = callback;
}

void KeyboardEventListener::setKeyboardKeyReleasedEventCallback(const KeyboardKeyReleasedEventCallback & callback)
{
  m_keyboard_key_released_event_callback = callback;
}

void KeyboardEventListener::invoke(const Event& event)
{
  invokeIfCasted(event,
                 m_keyboard_key_pressed_event_callback,
                 m_keyboard_key_released_event_callback);
}

} // namespace egnim::events