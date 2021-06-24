#ifndef PROJECT_EDITOR_H
#define PROJECT_EDITOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QDockWidget>
/* -------------------------------------------------------------------------- */

class Project;
class Document;
class DocumentManager;
class DialogWithToggleView;

class ProjectEditor : public QObject
{
  Q_OBJECT

public:
  enum StandardAction {
    CutAction            = 0x01,
    CopyAction           = 0x02,
    PasteAction          = 0x04,
    DeleteAction         = 0x08
  };
  Q_DECLARE_FLAGS(StandardActions, StandardAction)
  Q_FLAG(StandardActions)

public:
  ~ProjectEditor() override;

  virtual void setCurrentProject(Project* project) = 0;

  virtual void addProject(Project* project) = 0;
  virtual void removeProject(Project* project) = 0;

  virtual void openDocument(Document* document) = 0;
  virtual void closeDocument(Document* document) = 0;

  [[nodiscard]] virtual Project* getCurrentProject() const = 0;
  [[nodiscard]] virtual Document* getCurrentDocument() const = 0;

  [[nodiscard]] virtual QWidget* getEditorWidget() const = 0;

  virtual void saveState() = 0;
  virtual void restoreState() = 0;

  [[nodiscard]] virtual QList<QDockWidget*> getDockWidgets() const = 0;
  [[nodiscard]] virtual QList<DialogWithToggleView*> getDialogWidgets() const = 0;

  virtual void performStandardAction(StandardAction standard_action) = 0;
  [[nodiscard]] virtual StandardActions getEnabledStandardActions() const = 0;

Q_SIGNALS:
  void enabledStandardActionsChanged();
  void currentDocumentChanged(Document* document);

protected:
  explicit ProjectEditor(QObject* parent = nullptr);
};

#endif //PROJECT_EDITOR_H
