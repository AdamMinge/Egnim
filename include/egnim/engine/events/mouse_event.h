#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/events/event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events
{

  class EGNIM_UTILITY_API MouseEvent: public Event
  {
    EGNIM_CLASS(MouseEvent, Event)

  public:

  };

}; // namespace egnim::events

#endif //MOUSE_EVENT_H
