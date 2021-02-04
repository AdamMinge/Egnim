/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/command_queue.h>
#include <egnim/engine/core/command.h>
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
  m_commands.pop();
}

const Command& CommandQueue::front() const
{
  return *m_commands.front();
}

Command& CommandQueue::front()
{
  return *m_commands.front();
}

const Command& CommandQueue::back() const
{
  return *m_commands.back();
}

Command& CommandQueue::back()
{
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
  auto command = std::move(m_commands.front());
  m_commands.pop();
  return command;
}

} // namespace core


