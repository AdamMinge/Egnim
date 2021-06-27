/* ------------------------------------ Qt ---------------------------------- */
#include <QMainWindow>
/* ----------------------------------- Local -------------------------------- */
#include "project/game_editor.h"
#include "project/game_project.h"
#include "project/undo_dock.h"
#include "project/open_project_dock.h"
#include "project/open_documents_widget.h"
#include "document/scene_editor.h"
#include "preferences_manager.h"
#include "action_manager.h"
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
  m_open_documents_widget(new OpenDocumentsWidget()),
  m_undo_dock(new UndoDock(m_main_window.data())),
  m_file_system_dock(new OpenProjectDock(m_main_window.data())),
  m_preferences(new Preferences)
{
  m_open_documents_widget->addEditor(Document::Type::Scene, std::make_unique<SceneEditor>());

  m_main_window->setCentralWidget(m_open_documents_widget);

  m_main_window->setDockOptions(m_main_window->dockOptions() | QMainWindow::GroupedDragging);
  m_main_window->setDockNestingEnabled(true);

  m_main_window->addDockWidget(Qt::LeftDockWidgetArea, m_undo_dock);
  m_main_window->addDockWidget(Qt::LeftDockWidgetArea, m_file_system_dock);

  connect(m_open_documents_widget, &OpenDocumentsWidget::currentDocumentChanged, this, &GameEditor::currentDocumentChanged);
}

GameEditor::~GameEditor() = default;

void GameEditor::setCurrentProject(Project* project)
{
  if(m_current_project == project)
    return;

  if(m_current_project)
  {
    disconnect(m_current_project, &Project::addedDocument, this, &GameEditor::openDocument);
    disconnect(m_current_project, &Project::removedDocument, this, &GameEditor::closeDocument);
  }

  auto game_project = qobject_cast<GameProject*>(project);
  Q_ASSERT(game_project || !project);

  m_current_project = game_project;

  if(m_current_project)
  {
    connect(m_current_project, &Project::addedDocument, this, &GameEditor::openDocument);
    connect(m_current_project, &Project::removedDocument, this, &GameEditor::closeDocument);
  }

  m_open_documents_widget->setCurrentProject(project);
  m_undo_dock->setStack(game_project ? game_project->getUndoStack() : nullptr);
}

void GameEditor::addProject(Project* project)
{
  Q_ASSERT(project);
  m_open_documents_widget->addProject(project);
}

void GameEditor::removeProject(Project* project)
{
  Q_ASSERT(project);
  m_open_documents_widget->removeProject(project);
}

void GameEditor::openDocument(Document* document)
{
  Q_ASSERT(document);
  m_open_documents_widget->openDocument(document);
}

void GameEditor::closeDocument(Document* document)
{
  Q_ASSERT(document);
  m_open_documents_widget->closeDocument(m_open_documents_widget->findDocument(document));
}

Project* GameEditor::getCurrentProject() const
{
  return m_current_project;
}

Document* GameEditor::getCurrentDocument() const
{
  return m_open_documents_widget->getCurrentDocument();
}

QWidget* GameEditor::getEditorWidget() const
{
  return m_main_window.data();
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

  if(auto document_editor = m_open_documents_widget->getCurrentEditor(); document_editor)
    dockWidgets.append(document_editor->getDockWidgets());

  return dockWidgets;
}

QList<DialogWithToggleView*> GameEditor::getDialogWidgets() const
{
  auto dialogWidgets = QList<DialogWithToggleView*> { };

  if(auto document_editor = m_open_documents_widget->getCurrentEditor(); document_editor)
    dialogWidgets.append(document_editor->getDialogWidgets());

  return dialogWidgets;
}

void GameEditor::performStandardAction(StandardAction standard_action)
{
  // TODO : implementation //
}

GameEditor::StandardActions GameEditor::getEnabledStandardActions() const
{
  // TODO : implementation //
  GameEditor::StandardActions standard_actions;
  return standard_actions;
}
