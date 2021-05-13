/* ------------------------------------ Qt ---------------------------------- */
#include <QMainWindow>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/game_editor.h>
#include <egnim/editor/game_document.h>
#include <egnim/editor/undo_dock.h>
#include <egnim/editor/scene_dock.h>
#include <egnim/editor/inspector_dock.h>
#include <egnim/editor/file_system_dock.h>
/* -------------------------------------------------------------------------- */

GameEditor::GameEditor(QObject* parent) :
  Editor(parent),
  m_current_document(nullptr),
  m_main_window(new QMainWindow()),
  m_undo_dock(new UndoDock(m_main_window.data())),
  m_scene_dock(new SceneDock(m_main_window.data())),
  m_inspector_dock(new InspectorDock(m_main_window.data())),
  m_file_system_dock(new FileSystemDock(m_main_window.data()))
{
  m_main_window->setDockOptions(m_main_window->dockOptions() | QMainWindow::GroupedDragging);
  m_main_window->setDockNestingEnabled(true);

  m_main_window->addDockWidget(Qt::LeftDockWidgetArea, m_undo_dock);
  m_main_window->addDockWidget(Qt::LeftDockWidgetArea, m_file_system_dock);

  m_main_window->addDockWidget(Qt::RightDockWidgetArea, m_scene_dock);
  m_main_window->addDockWidget(Qt::RightDockWidgetArea, m_inspector_dock);
}

GameEditor::~GameEditor() = default;

void GameEditor::setCurrentDocument(Document* document)
{
  if(m_current_document == document)
    return;

  auto game_document = qobject_cast<GameDocument*>(document);
  Q_ASSERT(game_document || !document);

  m_current_document = game_document;

  m_undo_dock->setStack(game_document ? game_document->getUndoStack() : nullptr);
}

Document* GameEditor::getCurrentDocument() const
{
  return m_current_document;
}

QWidget* GameEditor::getEditorWidget() const
{
  return m_main_window.data();
}

void GameEditor::saveState()
{
 // TODO : implementation //
}

void GameEditor::restoreState()
{
  // TODO : implementation //
}

QList<QDockWidget*> GameEditor::getDockWidgets() const
{
  return QList<QDockWidget*> { m_undo_dock, m_scene_dock, m_inspector_dock, m_file_system_dock };
}

QList<DialogWithToggleView*> GameEditor::getDialogWidgets() const
{
  return QList<DialogWithToggleView*> {};
}