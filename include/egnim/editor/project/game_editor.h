#ifndef GAME_EDITOR_H
#define GAME_EDITOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QStackedWidget>
/* --------------------------------- Standard ------------------------------- */
#include <map>
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/project_editor.h>
/* -------------------------------------------------------------------------- */

class Document;
class UndoDock;
class GameProject;
class OpenProjectDock;
class OpenDocumentsWidget;

class GameEditor : public ProjectEditor
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit GameEditor(QObject* parent = nullptr);
  ~GameEditor() override;

  void setCurrentProject(Project* project) override;

  void addProject(Project* project) override;
  void removeProject(Project* project) override;

  void openDocument(Document* document) override;
  void closeDocument(Document* document) override;

  [[nodiscard]] Project* getCurrentProject() const override;
  [[nodiscard]] Document* getCurrentDocument() const override;

  [[nodiscard]] QWidget* getEditorWidget() const override;

  void saveState() override;
  void restoreState() override;

  [[nodiscard]] QList<QDockWidget*> getDockWidgets() const override;
  [[nodiscard]] QList<DialogWithToggleView*> getDialogWidgets() const override;

  void performStandardAction(StandardAction standard_action) override;
  [[nodiscard]] StandardActions getEnabledStandardActions() const override;

private:
  GameProject* m_current_project;
  QScopedPointer<QMainWindow> m_main_window;

  OpenDocumentsWidget* m_open_documents_widget;
  UndoDock* m_undo_dock;
  OpenProjectDock* m_file_system_dock;

  QScopedPointer<Preferences> m_preferences;
};

#endif //GAME_EDITOR_H
