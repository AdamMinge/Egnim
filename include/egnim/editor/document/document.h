#ifndef DOCUMENT_H
#define DOCUMENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QDateTime>
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
  [[nodiscard]] QDateTime getLastModified() const;

  [[nodiscard]] bool isModified() const;
  [[nodiscard]] QUndoStack* getUndoStack() const;

  bool save(const QString& file_name);
  static std::unique_ptr<Document> load(const QString& file_name);

  static QString getDocumentFileFilter();

  [[nodiscard]] QString getDocumentExtension() const;
  static QString getDocumentExtension(Type type);

Q_SIGNALS:
  void modifiedChanged();
  void fileNameChanged(const QString& new_file_name, const QString& old_file_name);

  void saved();

protected:
  explicit Document(Type type, QObject* parent = nullptr);

private:
  Type m_type;
  QString m_file_name;
  QUndoStack* m_undo_stack;
};

enum class Document::Type
{
  Scene,
  Unknown,
};

#endif //DOCUMENT_H
