#ifndef SCENE_EDITOR_H
#define SCENE_EDITOR_H

/* ----------------------------------- Local -------------------------------- */
#include "document/document_editor.h"
/* -------------------------------------------------------------------------- */

class SceneDocument;

class SceneDock;
class InspectorDock;

class SceneEditor : public DocumentEditor
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit SceneEditor(QObject* parent = nullptr);
  ~SceneEditor() override;

  void setCurrentDocument(Document* document) override;

  [[nodiscard]] Document* getCurrentDocument() const override;
  [[nodiscard]] QWidget* getEditorWidget() const override;

  void saveState() override;
  void restoreState() override;

  [[nodiscard]] QList<QDockWidget*> getDockWidgets() const override;
  [[nodiscard]] QList<DialogWithToggleView*> getDialogWidgets() const override;

private:
  SceneDocument* m_current_document;
  QScopedPointer<QMainWindow> m_main_window;

  SceneDock* m_scene_dock;
  InspectorDock* m_inspector_dock;

  QScopedPointer<Preferences> m_preferences;
};

#endif //SCENE_EDITOR_H
