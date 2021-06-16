#ifndef PROJECT_EDITOR_H
#define PROJECT_EDITOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QDockWidget>
/* -------------------------------------------------------------------------- */

class Project;
class DocumentManager;
class DialogWithToggleView;

class ProjectEditor : public QObject
{
  Q_OBJECT

public:
  enum StandardAction {
    CutAction           = 0x01,
    CopyAction          = 0x02,
    DeleteAction        = 0x04
  };
  Q_DECLARE_FLAGS(StandardActions, StandardAction)
  Q_FLAG(StandardActions)

public:
  ~ProjectEditor() override;

  virtual void setCurrentProject(Project* project) = 0;

  [[nodiscard]] virtual Project* getCurrentProject() const = 0;
  [[nodiscard]] virtual QWidget* getEditorWidget() const = 0;
  [[nodiscard]] virtual DocumentManager* getDocumentManager() const = 0;

  virtual void saveState() = 0;
  virtual void restoreState() = 0;

  [[nodiscard]] virtual QList<QDockWidget*> getDockWidgets() const = 0;
  [[nodiscard]] virtual QList<DialogWithToggleView*> getDialogWidgets() const = 0;

  [[nodiscard]] virtual StandardActions getEnabledStandardActions() const = 0;

protected:
  explicit ProjectEditor(QObject* parent = nullptr);
};

#endif //PROJECT_EDITOR_H
