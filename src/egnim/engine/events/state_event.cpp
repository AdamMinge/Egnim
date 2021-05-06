/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/state_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events {

/* --------------------------------- StateEvent ----------------------------- */

StateEvent::StateEvent(core::State& state) :
  Event(Type::State),
  m_state(std::addressof(state))
{

}

StateEvent::~StateEvent() = default;

void StateEvent::setState(core::State& state)
{
  m_state = std::addressof(state);
}

core::State& StateEvent::getState() const
{
  return *m_state;
}

/* ------------------------------- ActivatedState --------------------------- */

ActivatedState::ActivatedState(core::State& state) :
  StateEvent(state)
{

}

ActivatedState::~ActivatedState() = default;

/* ------------------------------- InactiveedState -------------------------- */

InactivatedState::InactivatedState(core::State& state) :
  StateEvent(state)
{

}

InactivatedState::~InactivatedState() = default;

} // namespace egnim::events

