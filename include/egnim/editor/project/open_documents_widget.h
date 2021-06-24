#ifndef OPEN_DOCUMENTS_WIDGET_H
#define OPEN_DOCUMENTS_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QStackedLayout>
#include <QStackedWidget>
#include <QScopedPointer>
#include <QObject>
#include <QTabBar>
#include <QHash>
/* --------------------------------- Standard ------------------------------- */
#include <unordered_map>
#include <memory>
#include <vector>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/document/document.h>
#include <egnim/editor/document/document_editor.h>
/* -------------------------------------------------------------------------- */

class NoDocumentWidget;
class Project;

class OpenDocumentsTabBar : public QWidget
{
Q_OBJECT

public:
  explicit OpenDocumentsTabBar(QWidget* parent = nullptr);
  ~OpenDocumentsTabBar() override;

  void openDocument(Document* document);
  void closeDocument(int index);
  void closeAllDocuments();

  [[nodiscard]] Document* getDocument(int index) const;
  [[nodiscard]] Document* getCurrentDocument() const;

  [[nodiscard]] int findDocument(Document *document) const;

  void switchToDocument(int index);
  void switchToDocument(Document* document);

Q_SIGNALS:
  void currentDocumentChanged(Document* document);

private Q_SLOTS:
  void currentIndexChanged();
  void documentTabMoved(int from, int to);
  void updateDocumentTab(Document* document);

private:
  QTabBar* m_tab_bar;
  std::vector<Document*> m_open_documents;
};

class OpenDocumentsWidget : public QWidget
{
  Q_OBJECT

public:
  explicit OpenDocumentsWidget(QWidget* parent = nullptr);
  ~OpenDocumentsWidget() override;

  void setCurrentProject(Project* project);

  void addProject(Project* project);
  void removeProject(Project* project);

  void addEditor(Document::Type document_type, std::unique_ptr<DocumentEditor> editor);
  void removeEditor(Document::Type document_type);
  void removeAllEditors();

  [[nodiscard]] DocumentEditor* getEditor(Document::Type document_type) const;
  [[nodiscard]] DocumentEditor* getCurrentEditor() const;

  void openDocument(Document* document);
  void closeDocument(int index);
  void closeAllDocuments();

  [[nodiscard]] Document* getDocument(int index) const;
  [[nodiscard]] Document* getCurrentDocument() const;

  [[nodiscard]] int findDocument(Document *document) const;

  void switchToDocument(int index);
  void switchToDocument(Document* document);

  void saveState();
  void restoreState();

Q_SIGNALS:
  void currentDocumentChanged(Document* document);

private Q_SLOTS:
  void projectCurrentDocumentChanged(Document* document);

private:
  Project* m_current_project;
  std::unordered_map<Project*, OpenDocumentsTabBar*> m_open_documents_for_project;

  std::unordered_map<Document::Type, std::unique_ptr<DocumentEditor>> m_editor_for_document_type;
  QScopedPointer<NoDocumentWidget> m_no_document_widget;
  QStackedLayout* m_editor_stack;
  QStackedWidget* m_project_documents_stack;
};

#endif //OPEN_DOCUMENTS_WIDGET_H
