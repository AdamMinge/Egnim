#ifndef DOCUMENT_MANAGER_H
#define DOCUMENT_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QStackedLayout>
#include <QScopedPointer>
#include <QUndoGroup>
#include <QObject>
#include <QTabBar>
#include <QHash>
/* --------------------------------- Standard ------------------------------- */
#include <unordered_map>
#include <memory>
#include <vector>
/* ----------------------------------- Local -------------------------------- */
#include "document/document.h"
#include "document/document_editor.h"
/* -------------------------------------------------------------------------- */

class NoDocumentWidget;
class FileSystemWatcher;

class DocumentManager : public QObject
{
Q_OBJECT

public:
  static DocumentManager& getInstance();
  static void deleteInstance();

public:
  ~DocumentManager() override;

  [[nodiscard]] QWidget *getWidget() const;

  void addEditor(Document::Type document_type, std::unique_ptr<DocumentEditor> editor);
  void removeEditor(Document::Type document_type);
  void removeAllEditors();

  [[nodiscard]] DocumentEditor *getEditor(Document::Type document_type) const;
  [[nodiscard]] DocumentEditor *getCurrentEditor() const;

  void addDocument(std::unique_ptr<Document> document);
  void insertDocument(int index, std::unique_ptr<Document> document);

  void removeDocument(int index);
  void removeAllDocuments();

  [[nodiscard]] Document *getDocument(int index) const;
  [[nodiscard]] Document *getCurrentDocument() const;

  [[nodiscard]] int findDocument(Document *document) const;
  [[nodiscard]] int findDocument(const QString& file_name) const;

  void switchToDocument(int index);
  void switchToDocument(Document *document);
  bool switchToDocument(const QString& file_name);

  [[nodiscard]] QUndoGroup* getUndoGroup() const;

  void saveState();
  void restoreState();

  bool saveDocument(Document *document);
  bool saveDocumentAs(Document* document);

  bool reloadDocumentAt(int index);
  bool loadDocument(const QString& file_name);

  [[nodiscard]] const std::vector<std::unique_ptr<Document>> &getDocuments() const;

Q_SIGNALS:
  void currentDocumentChanged(Document *document);
  void documentCloseRequested(int index);

protected:
  explicit DocumentManager();

private Q_SLOTS:
  void currentIndexChanged();
  void documentTabMoved(int from, int to);

  void filesChanged(const QStringList &file_names);
  void fileNameChanged(const QString& new_file_name, const QString& old_file_name);
  void updateDocumentTab(Document *document);

private:
  static QScopedPointer<DocumentManager> m_instance;

  std::vector<std::unique_ptr<Document>> m_documents;
  std::unordered_map<Document::Type, std::unique_ptr<DocumentEditor>> m_editor_for_document_type;

  QScopedPointer<QWidget> m_widget;
  QScopedPointer<NoDocumentWidget> m_no_document_widget;
  QTabBar *m_tab_bar;
  QStackedLayout *m_editor_stack;

  QScopedPointer<FileSystemWatcher> m_file_system_watcher;
  QUndoGroup* m_undo_group;
};

#endif //DOCUMENT_MANAGER_H
