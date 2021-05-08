/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/state_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events {

/* --------------------------------- StateEvent ----------------------------- */

StateEvent::StateEvent(core::State& state, std::string_view state_id) :
  Event(Type::State),
  m_state(std::addressof(state)),
  m_state_id(state_id)
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

void StateEvent::setStateId(std::string_view state_id)
{
  m_state_id = state_id;
}

std::string_view StateEvent::getStateId() const
{
  return m_state_id;
}

/* ------------------------------- ActivatedState --------------------------- */

ActivatedState::ActivatedState(core::State& state, std::string_view state_id) :
  StateEvent(state, state_id)
{

}

ActivatedState::~ActivatedState() = default;

/* ------------------------------- InactiveedState -------------------------- */

InactivatedState::InactivatedState(core::State& state, std::string_view state_id) :
  StateEvent(state, state_id)
{

}

InactivatedState::~InactivatedState() = default;

} // namespace egnim::events

