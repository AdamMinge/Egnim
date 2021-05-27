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

  [[nodiscard]] const QString& getFileName() const;
  [[nodiscard]] const QString& getDisplayName() const;

  [[nodiscard]] QUndoStack* getUndoStack() const;

protected:
  explicit Document(Type type, QString file_name, QString display_name, QObject* parent = nullptr);

private:
  Type m_type;
  QString m_file_name;
  QString m_display_name;
  QUndoStack* m_undo_stack;
};

enum class Document::Type
{
  Game,
};

#endif //DOCUMENT_H
