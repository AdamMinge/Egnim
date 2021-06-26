/* ------------------------------------ Qt ---------------------------------- */
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/main_window.h>
#include <egnim/editor/preferences_manager.h>
#include <egnim/editor/project/project_manager.h>
#include <egnim/editor/language_manager.h>
#include <egnim/editor/action_manager.h>
#include <egnim/editor/style_manager.h>
#include <egnim/editor/about_dialog.h>
#include <egnim/editor/settings_dialog.h>
#include <egnim/editor/widgets/dialog_with_toggle_view.h>
#include <egnim/editor/project/new_project_dialog.h>
#include <egnim/editor/project/game_editor.h>
#include <egnim/editor/document/new_document_dialog.h>
#include <egnim/editor/document/document.h>
#include <egnim/editor/commands/add_remove_document.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "ui_main_window.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct MainWindow::Preferences
{
  Preference<QByteArray> main_window_geometry = Preference<QByteArray>("main_window/geometry");
  Preference<QByteArray> main_window_state = Preference<QByteArray>("main_window/state");
  Preference<QString> open_project_start_location = Preference<QString>("project/open_project_start_location", QDir::homePath());
};

/* -------------------------------- MainWindow ------------------------------ */

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_ui(new Ui::MainWindow()),
  m_preferences(new Preferences),
  m_current_project(nullptr),
  m_current_document(nullptr)
{
  m_ui->setupUi(this);

  registerMenus();
  registerActions();

  setCentralWidget(getProjectManager().getWidget());

  auto undoGroup = getProjectManager().getUndoGroup();
  auto undoAction = undoGroup->createUndoAction(this, tr("&Undo"));
  auto redoAction = undoGroup->createRedoAction(this, tr("&Redo"));

  m_ui->m_menu_edit->insertAction(m_ui->m_action_cut, undoAction);
  m_ui->m_menu_edit->insertAction(m_ui->m_action_cut, redoAction);
  m_ui->m_menu_edit->insertSeparator(m_ui->m_action_cut);

  getActionManager().registerAction(undoAction, "undo");
  getActionManager().registerAction(redoAction, "redo");

  connect(undoGroup, &QUndoGroup::cleanChanged, this, &MainWindow::updateWindowTitle);

  getProjectManager().addEditor(Project::Type::Game, std::make_unique<GameEditor>());

  connect(getProjectManager().getEditor(Project::Type::Game), &ProjectEditor::enabledStandardActionsChanged, this, &MainWindow::updateActions);

  connect(getActionManager().findAction("new_project"), &QAction::triggered, this, [this](){
    newProject(Project::Type::Game);
  });
  connect(getActionManager().findAction("clear_recent_projects"), &QAction::triggered, this, &MainWindow::clearRecent);
  connect(getActionManager().findAction("open_project"), &QAction::triggered, this, qOverload<>(&MainWindow::openProject));
  connect(getActionManager().findAction("close_project"), &QAction::triggered, this, [this](){
    closeProject(getProjectManager().findProject(getProjectManager().getCurrentProject()));
  });
  connect(getActionManager().findAction("settings"), &QAction::triggered, this, &MainWindow::openSettings);
  connect(getActionManager().findAction("save_project"), &QAction::triggered, this, [this](){
    saveProject(getCurrentProject());
  });
  connect(getActionManager().findAction("save_all_projects"), &QAction::triggered, this, &MainWindow::saveAllProjects);
  connect(getActionManager().findAction("exit"), &QAction::triggered, this, &MainWindow::close);

  connect(getActionManager().findAction("new_scene_document"), &QAction::triggered, this, [this](){
    newDocument(Document::Type::Scene);
  });
  connect(getActionManager().findAction("close_document"), &QAction::triggered, this, &MainWindow::closeDocument);

  connect(getActionManager().findAction("cut"), &QAction::triggered, this, &MainWindow::performCut);
  connect(getActionManager().findAction("copy"), &QAction::triggered, this, &MainWindow::performCopy);
  connect(getActionManager().findAction("paste"), &QAction::triggered, this, &MainWindow::performPaste);
  connect(getActionManager().findAction("delete"), &QAction::triggered, this, &MainWindow::performDelete);

  connect(getActionManager().findAction("about"), &QAction::triggered, this, &MainWindow::openAbout);

  connect(getActionManager().findMenu("views_and_toolbars"), &QMenu::aboutToShow, this, &MainWindow::updateViewsAndToolbarsMenu);

  connect(&getProjectManager(), &ProjectManager::currentProjectChanged, this, &MainWindow::projectChanged);
  connect(&getProjectManager(), &ProjectManager::projectCloseRequested, this, &MainWindow::closeProject);

  connect(&getPreferencesManager(), &PreferencesManager::recentProjectFilesChanged, this, &MainWindow::updateRecentProjectFiles);

  updateActions();
  updateWindowTitle();
  updateRecentProjectFiles();

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
  if(auto editor = getProjectManager().getCurrentEditor(); editor)
  {
    disconnect(editor, &ProjectEditor::currentDocumentChanged, this, &MainWindow::documentChanged);
  }

  m_current_project = project;

  if(auto editor = getProjectManager().getCurrentEditor(); editor)
  {
    connect(editor, &ProjectEditor::currentDocumentChanged, this, &MainWindow::documentChanged);
  }

  updateActions();
  updateWindowTitle();
}

void MainWindow::documentChanged(Document* document)
{
  m_current_document = document;

  updateActions();
  updateWindowTitle();
}

void MainWindow::newProject(Project::Type type) // NOLINT(readability-make-member-function-const)
{
  auto new_project = createProject(type);
  if(new_project)
  {
    auto new_project_ptr = new_project.get();

    getProjectManager().addProject(std::move(new_project));
    saveProject(new_project_ptr);
  }
}

void MainWindow::openProject()
{
  auto file_names = QFileDialog::getOpenFileNames(this,
                                                  tr("Open Project"),
                                                  m_preferences->open_project_start_location.get(),
                                                  Project::getProjectFileFilter(),
                                                  nullptr,
                                                  QFileDialog::Options() | QFileDialog::Option::DontUseNativeDialog);

  if(file_names.isEmpty())
    return;

  m_preferences->open_project_start_location = QFileInfo(file_names.front()).path();

  for(auto& file_name : file_names)
    openProject(file_name);
}

void MainWindow::clearRecent() // NOLINT(readability-make-member-function-const)
{
  getPreferencesManager().clearRecentProjectFiles();
}

void MainWindow::openSettings()
{
  auto settings_dialog = new SettingsDialog(this);
  settings_dialog->setAttribute(Qt::WA_DeleteOnClose);
  settings_dialog->show();
}

void MainWindow::openAbout()
{
  auto about_dialog = new AboutDialog(this);
  about_dialog->setAttribute(Qt::WA_DeleteOnClose);
  about_dialog->show();
}

bool MainWindow::saveProject(Project* project) // NOLINT(readability-make-member-function-const)
{
  Q_ASSERT(project);
  getProjectManager().switchToProject(project);
  return getProjectManager().saveProject(project);
}

bool MainWindow::saveAllProjects() // NOLINT(readability-make-member-function-const)
{
  for(const auto& project : getProjectManager().getProjects()) // NOLINT(readability-use-anyofallof)
    if(!saveProject(project.get())) return false;

  return true;
}

void MainWindow::newDocument(Document::Type type) // NOLINT(readability-make-member-function-const)
{
  auto new_document = createDocument(type);
  if(new_document)
  {
    auto project = getCurrentProject();
    project->getUndoStack()->push(new AddDocument(*project, std::move(new_document)));
  }
}

void MainWindow::closeDocument() // NOLINT(readability-make-member-function-const)
{
  auto project_editor = getProjectManager().getCurrentEditor();
  auto document = project_editor ? project_editor->getCurrentDocument() : nullptr;

  if(project_editor && document)
    project_editor->closeDocument(document);
}

void MainWindow::performCut() // NOLINT(readability-make-member-function-const)
{
  if(auto editor = getProjectManager().getCurrentEditor())
    editor->performStandardAction(ProjectEditor::CutAction);
}

void MainWindow::performCopy() // NOLINT(readability-make-member-function-const)
{
  if(auto editor = getProjectManager().getCurrentEditor())
    editor->performStandardAction(ProjectEditor::CopyAction);
}

void MainWindow::performPaste() // NOLINT(readability-make-member-function-const)
{
  if(auto editor = getProjectManager().getCurrentEditor())
    editor->performStandardAction(ProjectEditor::PasteAction);
}

void MainWindow::performDelete() // NOLINT(readability-make-member-function-const)
{
  if(auto editor = getProjectManager().getCurrentEditor())
    editor->performStandardAction(ProjectEditor::DeleteAction);
}

void MainWindow::updateActions() // NOLINT(readability-make-member-function-const)
{
  auto project_editor = getProjectManager().getCurrentEditor();

  ProjectEditor::StandardActions standard_actions;
  if(project_editor)
    standard_actions = project_editor->getEnabledStandardActions();

  getActionManager().findAction("close_project")->setEnabled(m_current_project);
  getActionManager().findAction("save_project")->setEnabled(m_current_project);
  getActionManager().findAction("save_all_projects")->setEnabled(m_current_project);

  getActionManager().findMenu("document")->menuAction()->setVisible(m_current_project);
  getActionManager().findAction("new_scene_document")->setEnabled(m_current_project);
  getActionManager().findAction("close_document")->setEnabled(m_current_document);

  getActionManager().findAction("cut")->setEnabled(standard_actions & ProjectEditor::CutAction);
  getActionManager().findAction("copy")->setEnabled(standard_actions & ProjectEditor::CopyAction);
  getActionManager().findAction("paste")->setEnabled(standard_actions & ProjectEditor::PasteAction);
  getActionManager().findAction("delete")->setEnabled(standard_actions & ProjectEditor::DeleteAction);

  getActionManager().findMenu("views_and_toolbars")->setEnabled(m_current_project);
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

void MainWindow::updateRecentProjectFiles() // NOLINT(readability-make-member-function-const)
{
  auto recent_project_files = getPreferencesManager().getRecentProjectFiles();
  auto open_recent_project_menu = getActionManager().findMenu("open_recent_project");
  auto clear_recent_projects_action = getActionManager().findAction("clear_recent_projects");

  for(auto& action : open_recent_project_menu->actions())
  {
    if(action != clear_recent_projects_action)
      action->deleteLater();
  }

  for(auto& recent_project_file : recent_project_files)
  {
    auto fileInfo = QFileInfo(recent_project_file);
    if(!fileInfo.exists())
      continue;

    auto open_recent_project_action = new QAction(open_recent_project_menu);
    open_recent_project_action->setText(fileInfo.fileName());
    open_recent_project_action->setToolTip(fileInfo.filePath());
    open_recent_project_action->setVisible(true);

    open_recent_project_menu->insertAction(clear_recent_projects_action, open_recent_project_action);

    connect(open_recent_project_action, &QAction::triggered, this, [this, recent_project_file](){
      openProject(recent_project_file);
    });
  }

  open_recent_project_menu->insertSeparator(clear_recent_projects_action);
}

bool MainWindow::openProject(const QString& file_name) // NOLINT(readability-make-member-function-const)
{
  return getProjectManager().loadProject(file_name);
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
  for(const auto& project : getProjectManager().getProjects()) // NOLINT(readability-use-anyofallof)
    if(!confirmSave(project.get())) return false;

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
  getActionManager().registerMenu(m_ui->m_menu_project, "project");
  getActionManager().registerMenu(m_ui->m_menu_open_recent_project, "open_recent_project");

  getActionManager().registerMenu(m_ui->m_menu_document, "document");
  getActionManager().registerMenu(m_ui->m_menu_new_document, "new_document");

  getActionManager().registerMenu(m_ui->m_menu_edit, "edit");

  getActionManager().registerMenu(m_ui->m_menu_view, "view");
  getActionManager().registerMenu(m_ui->m_menu_views_and_toolbars, "views_and_toolbars");

  getActionManager().registerMenu(m_ui->m_menu_help, "help");
}

void MainWindow::registerActions()
{
  getActionManager().registerAction(m_ui->m_action_new_project, "new_project");
  getActionManager().registerAction(m_ui->m_action_open_project, "open_project");
  getActionManager().registerAction(m_ui->m_action_clear_recent_projects, "clear_recent_projects");
  getActionManager().registerAction(m_ui->m_action_close_project, "close_project");
  getActionManager().registerAction(m_ui->m_action_settings, "settings");
  getActionManager().registerAction(m_ui->m_action_save_project, "save_project");
  getActionManager().registerAction(m_ui->m_action_save_all_projects, "save_all_projects");
  getActionManager().registerAction(m_ui->m_action_exit, "exit");

  getActionManager().registerAction(m_ui->m_action_new_scene_document, "new_scene_document");
  getActionManager().registerAction(m_ui->m_action_close_document, "close_document");

  getActionManager().registerAction(m_ui->m_action_cut, "cut");
  getActionManager().registerAction(m_ui->m_action_copy, "copy");
  getActionManager().registerAction(m_ui->m_action_paste, "paste");
  getActionManager().registerAction(m_ui->m_action_delete, "delete");

  getActionManager().registerAction(m_ui->m_action_about, "about");
}

void MainWindow::retranslateUi()  // NOLINT(readability-make-member-function-const)
{
  getActionManager().findMenu("project")->setTitle(tr("&Project"));
  getActionManager().findMenu("open_recent_project")->setTitle(tr("Open &Recent"));
  getActionManager().findAction("new_project")->setText(tr("&New Project..."));
  getActionManager().findAction("open_project")->setText(tr("&Open..."));
  getActionManager().findAction("clear_recent_projects")->setText(tr("Clear &Recent"));
  getActionManager().findAction("close_project")->setText(tr("&Close Project"));
  getActionManager().findAction("settings")->setText(tr("&Settings..."));
  getActionManager().findAction("save_project")->setText(tr("&Save"));
  getActionManager().findAction("save_all_projects")->setText(tr("&Save All"));
  getActionManager().findAction("exit")->setText(tr("&Exit"));

  getActionManager().findMenu("document")->setTitle(tr("&Document"));
  getActionManager().findMenu("new_document")->setTitle(tr("&New"));
  getActionManager().findAction("new_scene_document")->setText(tr("New &Scene Document"));
  getActionManager().findAction("close_document")->setText(tr("&Close Document"));

  getActionManager().findMenu("edit")->setTitle(tr("&Edit"));
  getActionManager().findAction("undo")->setText(tr("&Undo"));
  getActionManager().findAction("redo")->setText(tr("&Redo"));
  getActionManager().findAction("cut")->setText(tr("&Cut"));
  getActionManager().findAction("copy")->setText(tr("&Copy"));
  getActionManager().findAction("paste")->setText(tr("&Paste"));
  getActionManager().findAction("delete")->setText(tr("&Delete"));

  getActionManager().findMenu("view")->setTitle(tr("&View"));
  getActionManager().findMenu("views_and_toolbars")->setTitle(tr("Views and &Toolbars"));

  getActionManager().findMenu("help")->setTitle(tr("&Help"));
  getActionManager().findAction("about")->setText(tr("&About..."));
}

