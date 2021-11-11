/* ------------------------------------ Qt ---------------------------------- */
#include <QMainWindow>
/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/document/scene_editor.h"
#include "egnim/tools/editor/document/scene_document.h"
#include "egnim/tools/editor/document/undo_dock.h"
#include "egnim/tools/editor/document/nodes_dock.h"
#include "egnim/tools/editor/document/inspector_dock.h"
#include "egnim/tools/editor/document/nodes_scene.h"
#include "egnim/tools/editor/document/nodes_view.h"
#include "egnim/tools/editor/preferences_manager.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct SceneEditor::Preferences
{
  Preference<QSize> editor_size = Preference<QSize>(QString("scene_editor/size"));
  Preference<QByteArray> editor_state = Preference<QByteArray>(QString("scene_editor/state"));
};

/* -------------------------------- SceneEditor ----------------------------- */

SceneEditor::SceneEditor(QObject* parent) :
  DocumentEditor(parent),
  m_current_document(nullptr),
  m_main_window(new QMainWindow()),
  m_scene_stack(new QStackedWidget(m_main_window.data())),
  m_undo_dock(new UndoDock(m_main_window.data())),
  m_scene_dock(new NodesDock(m_main_window.data())),
  m_inspector_dock(new InspectorDock(m_main_window.data())),
  m_preferences(new Preferences)
{
  m_main_window->setDockOptions(m_main_window->dockOptions() | QMainWindow::GroupedDragging);
  m_main_window->setDockNestingEnabled(true);

  m_main_window->setCentralWidget(m_scene_stack);

  m_main_window->addDockWidget(Qt::LeftDockWidgetArea, m_undo_dock);

  m_main_window->addDockWidget(Qt::RightDockWidgetArea, m_scene_dock);
  m_main_window->addDockWidget(Qt::RightDockWidgetArea, m_inspector_dock);
}

SceneEditor::~SceneEditor() = default;

void SceneEditor::setCurrentDocument(Document* document)
{
  if(m_current_document == document)
    return;

  auto scene_document = qobject_cast<SceneDocument*>(document);
  Q_ASSERT(scene_document || !document);

  m_current_document = scene_document;

  m_undo_dock->setStack(scene_document ? scene_document->getUndoStack() : nullptr);
}

void SceneEditor::addDocument(Document* document)
{
  auto scene_document = dynamic_cast<SceneDocument*>(document);
  Q_ASSERT(scene_document);

  auto view = new NodesView(m_scene_stack);
  auto scene = new NodesScene(view);

  view->setScene(scene);

  m_view_for_document.insert(scene_document, view);
  m_scene_stack->addWidget(view);
}

void SceneEditor::removeDocument(Document* document)
{
  auto scene_document = dynamic_cast<SceneDocument*>(document);
  Q_ASSERT(scene_document);
  Q_ASSERT(m_view_for_document.contains(scene_document));

  if(scene_document == m_current_document)
    setCurrentDocument(nullptr);

  auto view = m_view_for_document.take(scene_document);
  m_scene_stack->removeWidget(view);

  view->deleteLater();
}

Document* SceneEditor::getCurrentDocument() const
{
  return m_current_document;
}

QWidget* SceneEditor::getEditorWidget() const
{
  return m_main_window.data();
}

void SceneEditor::saveState()
{
  m_preferences->editor_state = m_main_window->saveState();
  m_preferences->editor_size = m_main_window->size();
}

void SceneEditor::restoreState()
{
  auto editor_size = static_cast<QSize>(m_preferences->editor_size);
  auto editor_state = static_cast<QByteArray>(m_preferences->editor_state);

  if(!editor_size.isNull())
    m_main_window->resize(editor_size);

  if(!editor_state.isNull())
    m_main_window->restoreState(editor_state);
}

QList<QDockWidget*> SceneEditor::getDockWidgets() const
{
  return QList<QDockWidget*> { m_undo_dock, m_scene_dock, m_inspector_dock };
}

QList<tools::QDialogWithToggleView*> SceneEditor::getDialogWidgets() const
{
  return QList<tools::QDialogWithToggleView*> {};
}

void SceneEditor::performStandardAction(StandardAction standard_action)
{
  // TODO : implementation //
}

SceneEditor::StandardActions SceneEditor::getEnabledStandardActions() const
{
  // TODO : implementation //
  SceneEditor::StandardActions standard_actions;
  return standard_actions;
}
