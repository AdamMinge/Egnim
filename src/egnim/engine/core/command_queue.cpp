/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/command_queue.h>
#include <egnim/engine/core/command.h>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* -------------------------------------------------------------------------- */

namespace core {

CommandQueue::CommandQueue() = default;

CommandQueue::~CommandQueue() = default;

void CommandQueue::push(std::unique_ptr<Command> command)
{
  m_commands.push(std::move(command));
}

void CommandQueue::pop()
{
  assert(!empty());
  m_commands.pop();
}

const Command& CommandQueue::front() const
{
  assert(!empty());
  return *m_commands.front();
}

Command& CommandQueue::front()
{
  assert(!empty());
  return *m_commands.front();
}

const Command& CommandQueue::back() const
{
  assert(!empty());
  return *m_commands.back();
}

Command& CommandQueue::back()
{
  assert(!empty());
  return *m_commands.back();
}

bool CommandQueue::empty() const
{
  return m_commands.empty();
}

size_t CommandQueue::size() const
{
  return m_commands.size();
}

std::unique_ptr<Command> CommandQueue::take()
{
  assert(!empty());
  auto command = std::move(m_commands.front());
  m_commands.pop();
  return command;
}

} // namespace core


