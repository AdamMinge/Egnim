/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/event_dispatcher.h>
#include <egnim/engine/events/priv/event_listener_vector.h>
/* -------------------------------------------------------------------------- */

namespace egnim::event {

EventDispatcher::EventDispatcher() :
  m_enabled(true)
{

}

EventDispatcher::~EventDispatcher() = default;

void EventDispatcher::addEventListener(EventListener* event_listener, scene::Node* node)
{

}

void EventDispatcher::addEventListener(EventListener* event_listener, int fixed_priority)
{

}

void EventDispatcher::removeEventListener(EventListener* event_listener)
{

}

void EventDispatcher::removeEventListener(scene::Node* node, bool recursive)
{

}

void EventDispatcher::removeEventListener(int32_t listen_events)
{

}

void EventDispatcher::dispatchEvent(Event& event)
{

}

void EventDispatcher::setEnabled(bool enabled)
{
  m_enabled = enabled;
}

bool EventDispatcher::isEnabled() const
{
  return m_enabled;
}

} // namespace egnim::event