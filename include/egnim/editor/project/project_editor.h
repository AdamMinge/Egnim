#ifndef PROJECT_EDITOR_H
#define PROJECT_EDITOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QDockWidget>
/* -------------------------------------------------------------------------- */

class Project;
class DialogWithToggleView;

class ProjectEditor : public QObject
{
  Q_OBJECT

public:
  ~ProjectEditor() override;

  virtual void setCurrentProject(Project* project) = 0;

  [[nodiscard]] virtual Project* getCurrentProject() const = 0;
  [[nodiscard]] virtual QWidget* getEditorWidget() const = 0;

  virtual void saveState() = 0;
  virtual void restoreState() = 0;

  [[nodiscard]] virtual QList<QDockWidget*> getDockWidgets() const = 0;
  [[nodiscard]] virtual QList<DialogWithToggleView*> getDialogWidgets() const = 0;

protected:
  explicit ProjectEditor(QObject* parent = nullptr);
};

#endif //PROJECT_EDITOR_H
