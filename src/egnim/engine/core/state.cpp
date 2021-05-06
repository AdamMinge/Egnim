/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/state.h>
#include <egnim/engine/core/state_stack.h>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* -------------------------------------------------------------------------- */

namespace egnim::core {

State::State(StateStack& state_stack, Context &context) :
  m_context(context),
  m_state_stack(state_stack)
{

}

State::~State() = default;

void State::onActive() {}

void State::onInactive() {}

void State::requestStackPush(std::string_view state_id)
{
  m_state_stack.pushState(state_id);
}

void State::requestStackPop()
{
  assert(m_state_stack.empty());
  m_state_stack.popState();
}

void State::requestStateClear()
{
  m_state_stack.clearStates();
}

Context& State::getContext()
{
  return m_context;
}

const Context& State::getContext() const
{
  return m_context;
}

StateStack& State::getStateStack()
{
  return m_state_stack;
}

const StateStack& State::getStateStack() const
{
  return m_state_stack;
}

} // namespace egnim::core


