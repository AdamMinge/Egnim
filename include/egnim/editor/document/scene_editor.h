#ifndef SCENE_EDITOR_H
#define SCENE_EDITOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QStackedWidget>
#include <QHash>
/* ----------------------------------- Local -------------------------------- */
#include "document/document_editor.h"
/* -------------------------------------------------------------------------- */

class SceneDocument;

class UndoDock;
class NodesDock;
class InspectorDock;
class NodesView;

class SceneEditor : public DocumentEditor
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit SceneEditor(QObject* parent = nullptr);
  ~SceneEditor() override;

  void setCurrentDocument(Document* document) override;

  void addDocument(Document* document) override;
  void removeDocument(Document* document) override;

  [[nodiscard]] Document* getCurrentDocument() const override;
  [[nodiscard]] QWidget* getEditorWidget() const override;

  void saveState() override;
  void restoreState() override;

  [[nodiscard]] QList<QDockWidget*> getDockWidgets() const override;
  [[nodiscard]] QList<DialogWithToggleView*> getDialogWidgets() const override;

  void performStandardAction(StandardAction standard_action) override;
  [[nodiscard]] StandardActions getEnabledStandardActions() const override;

private:
  SceneDocument* m_current_document;
  QScopedPointer<QMainWindow> m_main_window;

  QStackedWidget* m_scene_stack;
  UndoDock* m_undo_dock;
  NodesDock* m_scene_dock;
  InspectorDock* m_inspector_dock;

  QHash<SceneDocument*, NodesView*> m_view_for_document;

  QScopedPointer<Preferences> m_preferences;
};

#endif //SCENE_EDITOR_H
