#ifndef DOCUMENT_MANAGER_H
#define DOCUMENT_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QStackedLayout>
#include <QScopedPointer>
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

class DocumentManager : public QObject
{
  Q_OBJECT

public:
  explicit DocumentManager();
  ~DocumentManager() override;

  [[nodiscard]] QWidget* getWidget() const;

  void addEditor(Document::Type document_type, std::unique_ptr<DocumentEditor> editor);
  void removeEditor(Document::Type document_type);
  void removeAllEditors();

  [[nodiscard]] DocumentEditor* getEditor(Document::Type document_type) const;
  [[nodiscard]] DocumentEditor* getCurrentEditor() const;

  void addDocument(Document* document);
  void removeDocument(int index);
  void removeAllDocuments();

  [[nodiscard]] Document* getDocument(int index) const;
  [[nodiscard]] Document* getCurrentDocument() const;

  [[nodiscard]] int findDocument(Document *document) const;

  void switchToDocument(int index);
  void switchToDocument(Document* document);

  void saveState();
  void restoreState();

  [[nodiscard]] const std::vector<Document*>& getDocuments() const;

Q_SIGNALS:
  void currentDocumentChanged(Document* document);
  void documentCloseRequested(int index);

private Q_SLOTS:
  void currentIndexChanged();
  void documentTabMoved(int from, int to);
  void updateDocumentTab(Document* document);

private:
  std::vector<Document*> m_documents;
  std::unordered_map<Document::Type, std::unique_ptr<DocumentEditor>> m_editor_for_document_type;

  QScopedPointer<QWidget> m_widget;
  QScopedPointer<NoDocumentWidget> m_no_document_widget;
  QTabBar* m_tab_bar;
  QStackedLayout* m_editor_stack;
};

#endif //DOCUMENT_MANAGER_H
