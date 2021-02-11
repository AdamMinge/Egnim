#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H

/* --------------------------------- Standard ------------------------------- */
#include <queue>
#include <memory>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{
  class Command;

  class CommandQueue
  {
  public:
    explicit CommandQueue();
    ~CommandQueue();

    void push(std::unique_ptr<Command> command);
    void pop();

    [[nodiscard]] const Command& front() const;
    Command& front();

    [[nodiscard]] const Command& back() const;
    Command& back();

    [[nodiscard]] bool empty() const;
    [[nodiscard]] size_t size() const;

    std::unique_ptr<Command> take();

  private:
    std::queue<std::unique_ptr<Command>> m_commands;

  };

} // namespace egnim::core

#endif //COMMAND_QUEUE_H
