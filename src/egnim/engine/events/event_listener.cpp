/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/event_listener.h>
/* -------------------------------------------------------------------------- */

namespace egnim::event {

EventListener::EventListener(int32_t listen_events) :
  m_listen_events(listen_events),
  m_event_dispatcher(nullptr),
  m_enabled(true)
{

}

EventListener::~EventListener() = default;

int32_t EventListener::getListenEvents() const
{
  return  m_listen_events;
}

void EventListener::setEnabled(bool enabled)
{
  m_enabled = enabled;
}

bool EventListener::isEnabled() const
{
  return m_enabled;
}

EventDispatcher* EventListener::getEventDispatcher()
{
  return m_event_dispatcher;
}

const EventDispatcher* EventListener::getEventDispatcher() const
{
  return m_event_dispatcher;
}

void EventListener::setEventDispatcher(EventDispatcher* event_dispatcher)
{
  m_event_dispatcher = event_dispatcher;
}

} // namespace egnim::event