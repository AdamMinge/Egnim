/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/state_event_listener.h>
#include <egnim/engine/events/state_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events {

StateEventListener::StateEventListener() :
  EventListener(static_cast<int32_t>(Event::Type::State))
{

}

StateEventListener::~StateEventListener() = default;

void StateEventListener::setActivatedStateCallback(const ActivatedStateCallback& callback)
{
  m_activated_state_event_callback = callback;
}

void StateEventListener::setInactivatedStateCallback(const InactivatedStateCallback& callback)
{
  m_inactivated_state_event_callback = callback;
}

void StateEventListener::invoke(const Event& event)
{
  invokeIfCasted(event,
                 m_activated_state_event_callback,
                 m_inactivated_state_event_callback);
}

} // namespace egnim::events