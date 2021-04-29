/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/contact_event_listener.h>
#include <egnim/engine/events/contact_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events {

ContactEventListener::ContactEventListener() :
  EventListener(static_cast<int32_t>(Event::Type::Physics))
{

}

ContactEventListener::~ContactEventListener() = default;

void ContactEventListener::setBeginContactEventCallback(const BeginContactEventCallback &callback)
{
  m_begin_contact_event_callback = callback;
}

void ContactEventListener::setEndContactEventCallback(const EndContactEventCallback &callback)
{
  m_end_contact_event_callback = callback;
}

void ContactEventListener::setPreSolveContactEventCallback(const PreSolveContactEventCallback &callback)
{
  m_pre_solve_contact_event_callback = callback;
}

void ContactEventListener::setPostSolveContactEventCallback(const PostSolveContactEventCallback &callback)
{
  m_post_solve_contact_event_callback = callback;
}

void ContactEventListener::invoke(const Event &event)
{
  invokeIfCasted(event,
                 m_begin_contact_event_callback,
                 m_end_contact_event_callback,
                 m_pre_solve_contact_event_callback,
                 m_post_solve_contact_event_callback);
}

} // namespace egnim::events
