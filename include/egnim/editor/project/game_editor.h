#ifndef GAME_EDITOR_H
#define GAME_EDITOR_H

/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/project_editor.h>
/* -------------------------------------------------------------------------- */

class Document;
class GameProject;
class FileSystemDock;
class DocumentManager;

class GameEditor : public ProjectEditor
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit GameEditor(QObject* parent = nullptr);
  ~GameEditor() override;

  void setCurrentProject(Project* project) override;

  [[nodiscard]] Project* getCurrentProject() const override;
  [[nodiscard]] QWidget* getEditorWidget() const override;

  void saveState() override;
  void restoreState() override;

  [[nodiscard]] QList<QDockWidget*> getDockWidgets() const override;
  [[nodiscard]] QList<DialogWithToggleView*> getDialogWidgets() const override;

private Q_SLOTS:
  void closeDocument(int index);
  void documentChanged(Document* document);

private:
  GameProject* m_current_project;
  QScopedPointer<QMainWindow> m_main_window;
  QScopedPointer<DocumentManager> m_document_manager;

  FileSystemDock* m_file_system_dock;

  QScopedPointer<Preferences> m_preferences;
};

#endif //GAME_EDITOR_H
