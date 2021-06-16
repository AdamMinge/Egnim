/* ------------------------------------ Qt ---------------------------------- */
#include <QMainWindow>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/game_editor.h>
#include <egnim/editor/project/game_project.h>
#include <egnim/editor/project/undo_dock.h>
#include <egnim/editor/project/file_system_dock.h>
#include <egnim/editor/document/document_manager.h>
#include <egnim/editor/preferences_manager.h>
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct GameEditor::Preferences
{
  Preference<QSize> editor_size = Preference<QSize>(QString("game_editor/size"));
  Preference<QByteArray> editor_state = Preference<QByteArray>(QString("game_editor/state"));
};

/* -------------------------------- GameEditor ------------------------------ */

GameEditor::GameEditor(QObject* parent) :
  ProjectEditor(parent),
  m_current_project(nullptr),
  m_main_window(new QMainWindow()),
  m_undo_dock(new UndoDock(m_main_window.data())),
  m_document_manager(new DocumentManager()),
  m_file_system_dock(new FileSystemDock(m_main_window.data())),
  m_preferences(new Preferences)
{
  m_main_window->setDockOptions(m_main_window->dockOptions() | QMainWindow::GroupedDragging);
  m_main_window->setDockNestingEnabled(true);

  m_main_window->setCentralWidget(m_document_manager->getWidget());

  m_main_window->addDockWidget(Qt::LeftDockWidgetArea, m_undo_dock);
  m_main_window->addDockWidget(Qt::LeftDockWidgetArea, m_file_system_dock);
}

GameEditor::~GameEditor() = default;

void GameEditor::setCurrentProject(Project* project)
{
  if(m_current_project == project)
    return;

  auto game_project = qobject_cast<GameProject*>(project);
  Q_ASSERT(game_project || !project);

  m_current_project = game_project;

  m_undo_dock->setStack(game_project ? game_project->getUndoStack() : nullptr);
}

Project* GameEditor::getCurrentProject() const
{
  return m_current_project;
}

QWidget* GameEditor::getEditorWidget() const
{
  return m_main_window.data();
}

DocumentManager* GameEditor::getDocumentManager() const
{
  return m_document_manager.data();
}

void GameEditor::saveState()
{
  m_preferences->editor_state = m_main_window->saveState();
  m_preferences->editor_size = m_main_window->size();
}

void GameEditor::restoreState()
{
  auto editor_size = static_cast<QSize>(m_preferences->editor_size);
  auto editor_state = static_cast<QByteArray>(m_preferences->editor_state);

  if(!editor_size.isNull())
    m_main_window->resize(editor_size);

  if(!editor_state.isNull())
    m_main_window->restoreState(editor_state);
}

QList<QDockWidget*> GameEditor::getDockWidgets() const
{
  auto dockWidgets = QList<QDockWidget*> { m_undo_dock, m_file_system_dock };

  if(auto document_editor = m_document_manager->getCurrentEditor(); document_editor)
    dockWidgets.append(document_editor->getDockWidgets());

  return dockWidgets;
}

QList<DialogWithToggleView*> GameEditor::getDialogWidgets() const
{
  auto dialogWidgets = QList<DialogWithToggleView*> { };

  if(auto document_editor = m_document_manager->getCurrentEditor(); document_editor)
    dialogWidgets.append(document_editor->getDialogWidgets());

  return dialogWidgets;
}

GameEditor::StandardActions GameEditor::getEnabledStandardActions() const
{
  // TODO : implementation //
  GameEditor::StandardActions standard_actions;
  return standard_actions;
}

void GameEditor::closeDocument(int index)
{
  m_document_manager->removeDocument(index);
}
