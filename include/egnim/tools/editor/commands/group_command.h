#ifndef GROUP_COMMAND_H
#define GROUP_COMMAND_H

/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/commands/command.h"
/* -------------------------------------------------------------------------- */

class GroupCommand : public Command
{
public:
  explicit GroupCommand(Command* parent = nullptr);
  ~GroupCommand() override;

  void undo() override;
  void redo() override;

  [[nodiscard]] bool canMergeWith(const Command& other) const override;
  void mergeWith(const Command& other) override;

  void addCommand(Command* command);
  void removeCommand(Command* command);
  [[nodiscard]] const QList<Command*>& getCommands() const;

private:
  QList<Command*> m_commands;
};

#endif //GROUP_COMMAND_H
