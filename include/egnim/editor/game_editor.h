#ifndef GAME_EDITOR_H
#define GAME_EDITOR_H

/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/editor.h>
/* -------------------------------------------------------------------------- */

class GameDocument;

class UndoDock;
class SceneDock;
class InspectorDock;
class FileSystemDock;

class GameEditor : public Editor
{
  Q_OBJECT

public:
  explicit GameEditor(QObject* parent = nullptr);
  ~GameEditor() override;

  void setCurrentDocument(Document* document) override;

  [[nodiscard]] Document* getCurrentDocument() const override;
  [[nodiscard]] QWidget* getEditorWidget() const override;

  void saveState() override;
  void restoreState() override;

  [[nodiscard]] QList<QDockWidget*> getDockWidgets() const override;
  [[nodiscard]] QList<DialogWithToggleView*> getDialogWidgets() const override;

private:
  GameDocument* m_current_document;
  QScopedPointer<QMainWindow> m_main_window;

  UndoDock* m_undo_dock;
  SceneDock* m_scene_dock;
  InspectorDock* m_inspector_dock;
  FileSystemDock* m_file_system_dock;
};

#endif //GAME_EDITOR_H
