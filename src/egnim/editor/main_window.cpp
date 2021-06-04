/* ------------------------------------ Qt ---------------------------------- */
#include <QCloseEvent>
#include <QMessageBox>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/main_window.h>
#include <egnim/editor/preferences_manager.h>
#include <egnim/editor/project/project_manager.h>
#include <egnim/editor/language_manager.h>
#include <egnim/editor/action_manager.h>
#include <egnim/editor/style_manager.h>
#include <egnim/editor/widgets/dialog_with_toggle_view.h>
#include <egnim/editor/project/new_project_dialog.h>
#include <egnim/editor/project/game_editor.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "ui_main_window.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct MainWindow::Preferences
{
  Preference<QByteArray> main_window_geometry = Preference<QByteArray>("main_window/geometry");
  Preference<QByteArray> main_window_state = Preference<QByteArray>("main_window/state");
};

/* -------------------------------- MainWindow ------------------------------ */

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_ui(new Ui::MainWindow()),
  m_preferences(new Preferences),
  m_current_project(nullptr)
{
  m_ui->setupUi(this);

  registerMenus();
  registerActions();

  setCentralWidget(getProjectManager().getWidget());

  getProjectManager().addEditor(Project::Type::Game, std::make_unique<GameEditor>());

  connect(getActionManager().findAction("new_project"), &QAction::triggered, this, &MainWindow::newProject);
  connect(getActionManager().findAction("open_project"), &QAction::triggered, this, &MainWindow::openProject);
  connect(getActionManager().findAction("exit"), &QAction::triggered, this, &MainWindow::close);

  connect(getActionManager().findMenu("views_and_toolbars"), &QMenu::aboutToShow, this, &MainWindow::updateViewsAndToolbarsMenu);

  connect(&getProjectManager(), &ProjectManager::currentProjectChanged, this, &MainWindow::projectChanged);
  connect(&getProjectManager(), &ProjectManager::projectCloseRequested, this, &MainWindow::closeProject);

  updateActions();
  readSettings();
  retranslateUi();
}

MainWindow::~MainWindow()
{
  ProjectManager::deleteInstance();
  LanguageManager::deleteInstance();
  ActionManager::deleteInstance();
  StyleManager::deleteInstance();
  PreferencesManager::deleteInstance();
}

ProjectManager& MainWindow::getProjectManager() const
{
  return ProjectManager::getInstance();
}

LanguageManager& MainWindow::getLanguageManager() const
{
  return LanguageManager::getInstance();
}

StyleManager& MainWindow::getStyleManager() const
{
  return StyleManager::getInstance();
}

ActionManager& MainWindow::getActionManager() const
{
  return ActionManager::getInstance();
}

PreferencesManager& MainWindow::getPreferencesManager() const
{
  return PreferencesManager::getInstance();
}

Project* MainWindow::getCurrentProject() const
{
  return m_current_project;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  if (confirmAllSave())
  {
    writeSettings();
    event->accept();
  }
  else
  {
    event->ignore();
  }
}

void MainWindow::changeEvent(QEvent *event)
{
  QMainWindow::changeEvent(event);
  switch (event->type())
  {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void MainWindow::closeProject(int index)
{
  if (confirmSave(getProjectManager().getProject(index)))
    getProjectManager().removeProject(index);
}

void MainWindow::projectChanged(Project* project)
{
  m_current_project = project;

  updateActions();
  updateWindowTitle();
}

void MainWindow::newProject()
{
  auto new_project_dialog = new NewProjectDialog(this);
  new_project_dialog->setAttribute(Qt::WA_DeleteOnClose);
  new_project_dialog->show();
}

void MainWindow::openProject()
{
  // TODO : implementation //
}

void MainWindow::clearRecent()
{
  // TODO : implementation //
}

void MainWindow::openSettings()
{
  // TODO : implementation //
}

void MainWindow::openAbout()
{
  // TODO : implementation //
}

bool MainWindow::saveProject(Project* project) // NOLINT(readability-make-member-function-const)
{
  auto current_project = project;
  if(!current_project)
  {
    current_project = getProjectManager().getCurrentProject();
    if(!current_project)
      return false;
  }

  getProjectManager().switchToProject(current_project);
  getProjectManager().saveProject(current_project);

  return true;
}

bool MainWindow::saveAllProjects() // NOLINT(readability-make-member-function-const)
{
  for(const auto& document : getProjectManager().getProjects()) // NOLINT(readability-use-anyofallof)
    if(!saveProject(document.get())) return false;

  return true;
}

void MainWindow::updateActions()
{
  // TODO : implementation //
}

void MainWindow::updateWindowTitle()
{
  auto current_project = getProjectManager().getCurrentProject();

  auto project_name = current_project ? tr("[*]%1").arg(current_project->getDisplayName()) : QString();
  auto project_file_path = current_project ? current_project->getFileName() : QString();
  auto project_is_modified = current_project != nullptr && current_project->isModified();

  setWindowTitle(project_name);
  setWindowFilePath(project_file_path);
  setWindowModified(project_is_modified);
}

void MainWindow::updateViewsAndToolbarsMenu() // NOLINT(readability-make-member-function-const)
{
  auto view_and_toolbars_menu = getActionManager().findMenu("views_and_toolbars");
  view_and_toolbars_menu->clear();

  if(auto editor = getProjectManager().getCurrentEditor())
  {
    auto dockWidgets = editor->getDockWidgets();
    auto dialogWidgets = editor->getDialogWidgets();

    for(auto& dockWidget : dockWidgets)
      view_and_toolbars_menu->addAction(dockWidget->toggleViewAction());

    view_and_toolbars_menu->addSeparator();

    for(auto& dialogWidget : dialogWidgets)
      view_and_toolbars_menu->addAction(dialogWidget->toggleViewAction());
  }
}

bool MainWindow::confirmSave(Project* project)
{
  if(!project || !project->isModified())
    return true;

  getProjectManager().switchToProject(project);

  auto ret = QMessageBox::warning(
    this, tr("Unsaved Changes"),
    tr("There are unsaved changes. Do you want to save now?"),
    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

  switch (ret) {
    case QMessageBox::Save:    return saveProject(project);
    case QMessageBox::Discard: return true;
    case QMessageBox::Cancel:
    default:
      return false;
  }
}

bool MainWindow::confirmAllSave()
{
  for(const auto& document : getProjectManager().getProjects()) // NOLINT(readability-use-anyofallof)
    if(!confirmSave(document.get())) return false;

  return true;
}

void MainWindow::writeSettings()
{
  m_preferences->main_window_geometry = saveGeometry();
  m_preferences->main_window_state = saveState();

  getProjectManager().saveState();
}

void MainWindow::readSettings()
{
  auto main_window_geometry = static_cast<QByteArray>(m_preferences->main_window_geometry);
  auto main_window_state = static_cast<QByteArray>(m_preferences->main_window_state);

  if(!main_window_geometry.isNull())
    restoreGeometry(main_window_geometry);

  if(!main_window_state.isNull())
    restoreState(main_window_state);

  getProjectManager().restoreState();
}

void MainWindow::registerMenus()
{
  getActionManager().registerMenu(m_ui->m_menu_file, "file");
  getActionManager().registerMenu(m_ui->m_menu_new, "new");
  getActionManager().registerMenu(m_ui->m_menu_open_recent, "open_recent");

  getActionManager().registerMenu(m_ui->m_menu_edit, "edit");

  getActionManager().registerMenu(m_ui->m_menu_view, "view");
  getActionManager().registerMenu(m_ui->m_menu_views_and_toolbars, "views_and_toolbars");

  getActionManager().registerMenu(m_ui->m_menu_help, "help");
}

void MainWindow::registerActions()
{
  getActionManager().registerAction(m_ui->m_action_new_project, "new_project");
  getActionManager().registerAction(m_ui->m_action_open, "open_project");
  getActionManager().registerAction(m_ui->m_action_clear_recent, "clear_recent");
  getActionManager().registerAction(m_ui->m_action_close_project, "close_project");
  getActionManager().registerAction(m_ui->m_action_settings, "settings");
  getActionManager().registerAction(m_ui->m_action_save, "save");
  getActionManager().registerAction(m_ui->m_action_save_all, "save_all");
  getActionManager().registerAction(m_ui->m_action_exit, "exit");

  getActionManager().registerAction(m_ui->m_action_undo, "undo");
  getActionManager().registerAction(m_ui->m_action_redo, "redo");
  getActionManager().registerAction(m_ui->m_action_cut, "cut");
  getActionManager().registerAction(m_ui->m_action_copy, "copy");
  getActionManager().registerAction(m_ui->m_action_delete, "delete");

  getActionManager().registerAction(m_ui->m_action_about, "about");
}

void MainWindow::retranslateUi()
{
  // TODO : implementation //
}

