/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/commands/command.h>
/* -------------------------------------------------------------------------- */

Command::Command(Type type, Command* parent) :
  QUndoCommand(parent),
  m_type(type)
{

}

Command::~Command() = default;

bool Command::mergeWith(const QUndoCommand* other)
{
  auto command = dynamic_cast<const Command*>(other);
  if(!canMergeWith(*command))
    return false;

  mergeWith(*command);
  return true;
}

bool Command::canMergeWith(const Command& other) const
{
  return false;
}

void Command::mergeWith(const Command& other)
{
  Q_UNUSED(other);
}

Command::Type Command::getType() const
{
  return m_type;
}

int Command::id() const
{
  return static_cast<int>(getType());
}