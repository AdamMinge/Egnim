#ifndef PROJECT_H
#define PROJECT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QDateTime>
#include <QUndoStack>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <list>
/* -------------------------------------------------------------------------- */

class Document;

class Project : public QObject
{
  Q_OBJECT

public:
  enum class Type;

public:
  ~Project() override;

  [[nodiscard]] Type getType() const;

  void setFileName(const QString& file_name);
  [[nodiscard]] const QString& getFileName() const;

  [[nodiscard]] QString getDisplayName() const;
  [[nodiscard]] const QDateTime& getLastModified() const;

  [[nodiscard]] bool isModified() const;
  [[nodiscard]] QUndoStack* getUndoStack() const;

  void addDocument(std::unique_ptr<Document> document);
  std::unique_ptr<Document> removeDocument(const Document& document);
  void removeAllDocuments();

  [[nodiscard]] const std::list<std::unique_ptr<Document>>& getDocuments() const;

  bool save(const QString& file_name);
  static std::unique_ptr<Project> load(const QString& file_name);

  static QString getProjectFileFilter();

  [[nodiscard]] QString getProjectExtension() const;
  static QString getProjectExtension(Type type);

Q_SIGNALS:
  void modifiedChanged();
  void fileNameChanged(const QString& new_file_name, const QString& old_file_name);

  void addedDocument(Document* document);
  void removedDocument(Document* document);

  void saved();

protected:
  explicit Project(Type m_type, QObject* parent = nullptr);

  void setLastModified(const QDateTime& date_time);

private:
  Type m_type;
  QString m_file_name;
  std::list<std::unique_ptr<Document>> m_documents;
  QDateTime m_last_modified;
  QUndoStack* m_undo_stack;
};

enum class Project::Type
{
  Game,
};

#endif //PROJECT_H
