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

  void setFileName(const QString& file_name);
  [[nodiscard]] const QString& getFileName() const;

  [[nodiscard]] QString getDisplayName() const;

  [[nodiscard]] QUndoStack* getUndoStack() const;

  [[nodiscard]] bool isModified() const;

Q_SIGNALS:
  void modifiedChanged();
  void fileNameChanged(const QString& new_file_name, const QString& old_file_name);

protected:
  explicit Document(Type type, QString file_name, QObject* parent = nullptr);

private:
  Type m_type;
  QString m_file_name;
  QUndoStack* m_undo_stack;
};

enum class Document::Type
{
  Game,
};

#endif //DOCUMENT_H
