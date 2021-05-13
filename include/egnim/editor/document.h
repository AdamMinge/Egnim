#ifndef DOCUMENT_H
#define DOCUMENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QUndoStack>
/* -------------------------------------------------------------------------- */

class Document : public QObject
{
  Q_OBJECT

public:
  enum class Type;

public:
  ~Document() override;

  [[nodiscard]] Type getType() const;

  [[nodiscard]] QStringView getFileName() const;
  [[nodiscard]] QStringView getDisplayName() const;

  [[nodiscard]] QUndoStack* getUndoStack() const;

protected:
  explicit Document(Type type, QStringView file_name, QStringView display_name, QObject* parent = nullptr);

private:
  Type m_type;
  QStringView m_file_name;
  QStringView m_display_name;
  QUndoStack* m_undo_stack;
};

enum class Document::Type
{
  Game,
};

#endif //DOCUMENT_H
