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

  class EGNIM_UTILITY_API KeyboardEventListener: public EventListener
  {
    EGNIM_CLASS(KeyboardEventListener, EventListener)

  public:
  };

} // namespace egnim::events

#endif //KEYBOARD_EVENT_LISTENER_H
