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
#include <document.h>
#include <editor.h>
/* -------------------------------------------------------------------------- */

class DocumentManager : public QObject
{
  Q_OBJECT

public:
  static DocumentManager& getInstance();
  static void deleteInstance();

public:
  ~DocumentManager() override;

  [[nodiscard]] QWidget* getWidget() const;

  void addEditor(Document::Type document_type, std::unique_ptr<Editor> editor);
  void removeEditor(Document::Type document_type);
  void removeAllEditors();

  [[nodiscard]] Editor* getEditor(Document::Type document_type) const;
  [[nodiscard]] Editor* getCurrentEditor() const;

  void addDocument(std::unique_ptr<Document> document);
  void removeDocument(int index);
  void removeAllDocuments();

  [[nodiscard]] Document* getDocument(int index) const;
  [[nodiscard]] Document* getCurrentDocument() const;

  void switchToDocument(int index);
  void switchToDocument(Document* document);

  [[nodiscard]] QUndoGroup* undoGroup() const;

  void saveState();
  void restoreState();

Q_SIGNALS:
  void currentDocumentChanged(Document* document);
  void documentCloseRequested(int index);

private Q_SLOTS:
  void currentIndexChanged();
  void documentTabMoved(int from, int to);

private:
  explicit DocumentManager();

private:
  static QScopedPointer<DocumentManager> m_instance;

  std::vector<std::unique_ptr<Document>> m_documents;
  std::unordered_map<Document::Type, std::unique_ptr<Editor>> m_editor_for_document_type;

  QScopedPointer<QWidget> m_widget;
  QWidget* m_no_editor_widget;
  QTabBar* m_tab_bar;
  QStackedLayout* m_editor_stack;

  QUndoGroup* m_undo_group;
};

#endif //DOCUMENT_MANAGER_H
