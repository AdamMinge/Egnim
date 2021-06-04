#ifndef PROJECT_H
#define PROJECT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
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

  [[nodiscard]] bool isModified() const;

  void addDocument(std::unique_ptr<Document> document);
  void removeDocument(const Document& document);
  void removeAllDocuments();

  [[nodiscard]] const std::list<std::unique_ptr<Document>>& getDocuments() const;

  virtual bool save() = 0;

Q_SIGNALS:
  void modifiedChanged();
  void fileNameChanged(const QString& new_file_name, const QString& old_file_name);

  void addedDocument(Document* document);
  void removedDocument(Document* document);

protected:
  explicit Project(Type m_type, QString file_name, QObject* parent = nullptr);

private:
  Type m_type;
  QString m_file_name;
  std::list<std::unique_ptr<Document>> m_documents;
};

enum class Project::Type
{
  Game,
};

#endif //PROJECT_H
