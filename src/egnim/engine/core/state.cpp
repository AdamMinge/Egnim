/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/state.h>
#include <egnim/engine/core/state_stack.h>
/* -------------------------------------------------------------------------- */

namespace core {

State::State(StateStack& state_stack, Context &context) :
  m_context(context),
  m_state_stack(state_stack)
{

}

State::~State() = default;

void State::onActive() {}

void State::onInactive() {}

void State::onCreate() {}

void State::onDestroy() {}

void State::requestStackPush(std::string_view state_id)
{
  m_state_stack.pushState(state_id);
}

void State::requestStackPop()
{
  m_state_stack.popState();
}

void State::requestStateClear()
{
  m_state_stack.clearStates();
}

} // namespace core


