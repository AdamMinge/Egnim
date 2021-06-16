/* ------------------------------------ Qt ---------------------------------- */
#include <QMainWindow>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/document/scene_editor.h>
#include <egnim/editor/document/scene_document.h>
#include <egnim/editor/document/scene_dock.h>
#include <egnim/editor/document/inspector_dock.h>
#include <egnim/editor/preferences_manager.h>
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
  m_scene_dock(new SceneDock(m_main_window.data())),
  m_inspector_dock(new InspectorDock(m_main_window.data())),
  m_preferences(new Preferences)
{
  m_main_window->setDockOptions(m_main_window->dockOptions() | QMainWindow::GroupedDragging);
  m_main_window->setDockNestingEnabled(true);

  m_main_window->addDockWidget(Qt::RightDockWidgetArea, m_scene_dock);
  m_main_window->addDockWidget(Qt::RightDockWidgetArea, m_inspector_dock);
}

SceneEditor::~SceneEditor() = default;

void SceneEditor::setCurrentDocument(Document* document)
{
  if(m_current_document == document)
    return;

  auto game_document = qobject_cast<SceneDocument*>(document);
  Q_ASSERT(game_document || !document);

  m_current_document = game_document;
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
  return QList<QDockWidget*> { m_scene_dock, m_inspector_dock };
}

QList<DialogWithToggleView*> SceneEditor::getDialogWidgets() const
{
  return QList<DialogWithToggleView*> {};
}
