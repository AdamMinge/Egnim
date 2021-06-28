#ifndef COMMAND_H
#define COMMAND_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QUndoCommand>
/* -------------------------------------------------------------------------- */

class Command : public QUndoCommand
{
public:
  enum class Type;

public:
  explicit Command(Type type, Command* parent = nullptr);
  ~Command() override;

  bool mergeWith(const QUndoCommand* other) override;

  [[nodiscard]] virtual bool canMergeWith(const Command& other) const;
  virtual void mergeWith(const Command& other);

  [[nodiscard]] Type getType() const;
  [[nodiscard]] int id() const override;

private:
  Type m_type;
};

enum class Command::Type
{
  GroupCommand,
  AddDocument,
  RemoveDocument
};

#endif //COMMAND_H
