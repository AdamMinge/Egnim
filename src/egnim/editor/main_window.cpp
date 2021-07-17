/* ------------------------------------ Qt ---------------------------------- */
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
/* ----------------------------------- Local -------------------------------- */
#include "main_window.h"
#include "preferences_manager.h"
#include "language_manager.h"
#include "action_manager.h"
#include "style_manager.h"
#include "about_dialog.h"
#include "settings_dialog.h"
#include "project/project_manager.h"
#include "project/no_project_widget.h"
#include "project/project_dock.h"
#include "project/console_dock.h"
#include "project/export_project_dialog.h"
#include "document/new_document_dialog.h"
#include "document/document_manager.h"
#include "document/scene_editor.h"
#include "document/document.h"
#include "widgets/dialog_with_toggle_view.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "ui_main_window.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct MainWindow::Preferences
{
  Preference<QByteArray> main_window_geometry = Preference<QByteArray>("main_window/geometry");
  Preference<QByteArray> main_window_state = Preference<QByteArray>("main_window/state");
  Preference<QByteArray> project_window_geometry = Preference<QByteArray>("project_window/geometry");
  Preference<QByteArray> project_window_state = Preference<QByteArray>("project_window/state");
  Preference<QString> open_project_start_location = Preference<QString>("project/open_project_start_location", QDir::homePath());
  Preference<QLocale> application_language = Preference<QLocale>("application/language");
  Preference<QString> application_style = Preference<QString>("application/style");
};

/* -------------------------------- MainWindow ------------------------------ */

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_ui(new Ui::MainWindow()),
  m_preferences(new Preferences),
  m_stacked_widget(new QStackedWidget(this))
{
  m_ui->setupUi(this);

  registerMenus();
  registerActions();
  registerConnections();

  setCentralWidget(m_stacked_widget);
  m_no_project_widget = new NoProjectWidget(this);
  m_project_window = new QMainWindow(this);
  m_project_dock = new ProjectDock(m_project_window);
  m_console_dock = new ConsoleDock(m_project_window);

  m_project_window->setCentralWidget(getDocumentManager().getWidget());
  m_project_window->addDockWidget(Qt::LeftDockWidgetArea, m_project_dock);
  m_project_window->addDockWidget(Qt::BottomDockWidgetArea, m_console_dock);

  m_stacked_widget->addWidget(m_project_window);
  m_stacked_widget->addWidget(m_no_project_widget);

  getDocumentManager().addEditor(Document::Type::Scene, std::make_unique<SceneEditor>());
  connect(getDocumentManager().getEditor(Document::Type::Scene),
          &DocumentEditor::enabledStandardActionsChanged, this, &MainWindow::updateActions);

  projectChanged(getProjectManager().getProject());

  updateActions();
  updateWindowTitle();
  updateRecentProjectFiles();

  readSettings();
  retranslateUi();
}

MainWindow::~MainWindow()
{
  ProjectManager::deleteInstance();
  DocumentManager::deleteInstance();
  LanguageManager::deleteInstance();
  ActionManager::deleteInstance();
  StyleManager::deleteInstance();
  PreferencesManager::deleteInstance();
}

ProjectManager& MainWindow::getProjectManager() const
{
  return ProjectManager::getInstance();
}

DocumentManager& MainWindow::getDocumentManager() const
{
  return DocumentManager::getInstance();
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

void MainWindow::closeEvent(QCloseEvent *event)
{
  if (confirmAllSave() && closeProject())
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

void MainWindow::documentChanged(Document* document)
{
  updateActions();
}

void MainWindow::projectChanged(Project* project)
{
  m_stacked_widget->setCurrentWidget(project ? static_cast<QWidget*>(m_project_window) : m_no_project_widget);
  getDocumentManager().removeAllDocuments();

  m_project_dock->setCurrentProject(project);

  updateWindowTitle();
  updateActions();
}

bool MainWindow::confirmSave(Document* document)
{
  if(!document || !document->isModified())
    return true;

  getDocumentManager().switchToDocument(document);

  auto ret = QMessageBox::warning(
    this, tr("Unsaved Changes"),
    tr("There are unsaved changes. Do you want to save now?"),
    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

  switch (ret) {
    case QMessageBox::Save:    return saveDocument(document);
    case QMessageBox::Discard: return true;
    case QMessageBox::Cancel:
    default:
      return false;
  }
}

bool MainWindow::confirmAllSave()
{
  for(const auto& project : getDocumentManager().getDocuments()) // NOLINT(readability-use-anyofallof)
    if(!confirmSave(project.get())) return false;

  return true;
}

void MainWindow::updateActions() // NOLINT(readability-make-member-function-const)
{
  auto document_editor = getDocumentManager().getCurrentEditor();
  auto current_document = getDocumentManager().getCurrentDocument();
  auto current_project = getProjectManager().getProject();

  DocumentEditor::StandardActions standard_actions;
  if(document_editor)
    standard_actions = document_editor->getEnabledStandardActions();

  getActionManager().findAction("close_project")->setEnabled(current_project);
  getActionManager().findAction("export_project")->setEnabled(current_project);

  getActionManager().findMenu("document")->menuAction()->setVisible(current_project);
  getActionManager().findAction("new_scene_document")->setEnabled(current_project);
  getActionManager().findAction("close_document")->setEnabled(current_document);
  getActionManager().findAction("save_document")->setEnabled(current_document);
  getActionManager().findAction("save_document_as")->setEnabled(current_document);
  getActionManager().findAction("save_all_documents")->setEnabled(current_document);

  getActionManager().findAction("cut")->setEnabled(standard_actions & DocumentEditor::CutAction);
  getActionManager().findAction("copy")->setEnabled(standard_actions & DocumentEditor::CopyAction);
  getActionManager().findAction("paste")->setEnabled(standard_actions & DocumentEditor::PasteAction);
  getActionManager().findAction("delete")->setEnabled(standard_actions & DocumentEditor::DeleteAction);

  getActionManager().findMenu("views_and_toolbars")->setEnabled(current_project);
}

void MainWindow::updateWindowTitle()
{
  auto current_project = getProjectManager().getProject();

  auto project_name = current_project ? QString("[*]%1").arg(current_project->getDisplayName()) : QString();
  auto project_file_path = current_project ? current_project->getFileName() : QString();

  setWindowTitle(project_name);
  setWindowFilePath(project_file_path);
}

void MainWindow::updateViewsAndToolbarsMenu() // NOLINT(readability-make-member-function-const)
{
  auto view_and_toolbars_menu = getActionManager().findMenu("views_and_toolbars");
  view_and_toolbars_menu->clear();

  view_and_toolbars_menu->addAction(m_project_dock->toggleViewAction());
  view_and_toolbars_menu->addAction(m_console_dock->toggleViewAction());
  view_and_toolbars_menu->addSeparator();

  if(auto editor = getDocumentManager().getCurrentEditor())
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
      getProjectManager().loadProject(recent_project_file);
    });
  }

  open_recent_project_menu->insertSeparator(clear_recent_projects_action);
}

void MainWindow::newProject(Project::Type type) // NOLINT(readability-make-member-function-const)
{
  getProjectManager().newProject(type);
}

void MainWindow::openProject()
{
  auto file_name = QFileDialog::getOpenFileName(
    this,
    tr("Open Project"),
    m_preferences->open_project_start_location.get(),
    Project::getProjectFileFilter(),
    nullptr,
    QFileDialog::Options() | QFileDialog::Option::DontUseNativeDialog);

  if(file_name.isEmpty())
    return;

  getProjectManager().loadProject(file_name);
}

void MainWindow::clearRecent() // NOLINT(readability-make-member-function-const)
{
  getPreferencesManager().clearRecentProjectFiles();
}

bool MainWindow::closeProject() // NOLINT(readability-make-member-function-const)
{
  return getProjectManager().closeProject();
}

void MainWindow::openSettings()
{
  if(!m_settings_dialog)
  {
    m_settings_dialog = new SettingsDialog();
    m_settings_dialog->setAttribute(Qt::WA_DeleteOnClose);
  }

  m_settings_dialog->exec();
}

void MainWindow::exportProject()
{
  if(!m_external_project_dialog)
  {
    m_external_project_dialog = new ExportProjectDialog();
    m_external_project_dialog->setAttribute(Qt::WA_DeleteOnClose);
  }

  m_external_project_dialog->exec();
}

void MainWindow::newDocument(Document::Type type)
{
  m_project_dock->newDocument(type);
}

void MainWindow::closeDocument(int index) // NOLINT(readability-make-member-function-const)
{
  if(confirmSave(getDocumentManager().getDocument(index)))
    getDocumentManager().removeDocument(index);
}

bool MainWindow::saveDocument(Document* document) // NOLINT(readability-make-member-function-const)
{
  Q_ASSERT(document);
  getDocumentManager().switchToDocument(document);
  return getDocumentManager().saveDocument(document);
}

bool MainWindow::saveDocumentAs(Document* document) // NOLINT(readability-make-member-function-const)
{
  Q_ASSERT(document);
  getDocumentManager().switchToDocument(document);
  return getDocumentManager().saveDocumentAs(document);
}

bool MainWindow::saveAllDocuments()
{
  for(const auto& document : getDocumentManager().getDocuments()) // NOLINT(readability-use-anyofallof)
    if(!saveDocument(document.get())) return false;

  return true;
}

void MainWindow::performCut() // NOLINT(readability-make-member-function-const)
{
  if(auto editor = getDocumentManager().getCurrentEditor())
    editor->performStandardAction(DocumentEditor::CutAction);
}

void MainWindow::performCopy() // NOLINT(readability-make-member-function-const)
{
  if(auto editor = getDocumentManager().getCurrentEditor())
    editor->performStandardAction(DocumentEditor::CopyAction);
}

void MainWindow::performPaste() // NOLINT(readability-make-member-function-const)
{
  if(auto editor = getDocumentManager().getCurrentEditor())
    editor->performStandardAction(DocumentEditor::PasteAction);
}

void MainWindow::performDelete() // NOLINT(readability-make-member-function-const)
{
  if(auto editor = getDocumentManager().getCurrentEditor())
    editor->performStandardAction(DocumentEditor::DeleteAction);
}

void MainWindow::openAbout()
{
  if(!m_about_dialog)
  {
    m_about_dialog = new AboutDialog(this);
    m_about_dialog->setAttribute(Qt::WA_DeleteOnClose);
  }

  m_about_dialog->show();
  m_about_dialog->activateWindow();
  m_about_dialog->raise();
}

void MainWindow::writeSettings()
{
  m_preferences->main_window_geometry = saveGeometry();
  m_preferences->main_window_state = saveState();

  m_preferences->project_window_geometry = m_project_window->saveGeometry();
  m_preferences->project_window_state = m_project_window->saveState();

  m_preferences->application_language = getLanguageManager().getCurrentLanguage();
  m_preferences->application_style = getStyleManager().getCurrentStyle();

  getDocumentManager().saveState();
}

void MainWindow::readSettings()
{
  auto main_window_geometry = m_preferences->main_window_geometry.get();
  auto main_window_state = m_preferences->main_window_state.get();

  auto project_window_geometry = m_preferences->project_window_geometry.get();
  auto project_window_state = m_preferences->project_window_state.get();

  auto application_language = m_preferences->application_language.get();
  auto application_style = m_preferences->application_style.get();

  if(!main_window_geometry.isNull()) restoreGeometry(main_window_geometry);
  if(!main_window_state.isNull()) restoreState(main_window_state);

  if(!project_window_geometry.isNull()) m_project_window->restoreGeometry(project_window_geometry);
  if(!project_window_state.isNull()) m_project_window->restoreState(project_window_state);

  auto languages = getLanguageManager().getAvailableLanguages();
  if(languages.contains(application_language))
    getLanguageManager().setLanguage(application_language);
  else if(languages.contains(QLocale::system()))
    getLanguageManager().setLanguage(QLocale::system());

  if(!application_style.isEmpty())
    getStyleManager().setStyle(application_style);

  getDocumentManager().restoreState();
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
  getActionManager().registerAction(m_ui->m_action_export, "export_project");
  getActionManager().registerAction(m_ui->m_action_exit, "exit");

  getActionManager().registerAction(m_ui->m_action_new_scene_document, "new_scene_document");
  getActionManager().registerAction(m_ui->m_action_close_document, "close_document");
  getActionManager().registerAction(m_ui->m_action_save_document, "save_document");
  getActionManager().registerAction(m_ui->m_action_save_document_as, "save_document_as");
  getActionManager().registerAction(m_ui->m_action_save_all_documents, "save_all_documents");

  getActionManager().registerAction(m_ui->m_action_cut, "cut");
  getActionManager().registerAction(m_ui->m_action_copy, "copy");
  getActionManager().registerAction(m_ui->m_action_paste, "paste");
  getActionManager().registerAction(m_ui->m_action_delete, "delete");

  getActionManager().registerAction(m_ui->m_action_about, "about");
}

void MainWindow::registerConnections()
{
  auto undoGroup = getDocumentManager().getUndoGroup();
  auto undoAction = undoGroup->createUndoAction(this, tr("&Undo"));
  auto redoAction = undoGroup->createRedoAction(this, tr("&Redo"));

  m_ui->m_menu_edit->insertAction(m_ui->m_action_cut, undoAction);
  m_ui->m_menu_edit->insertAction(m_ui->m_action_cut, redoAction);
  m_ui->m_menu_edit->insertSeparator(m_ui->m_action_cut);

  getActionManager().registerAction(undoAction, "undo");
  getActionManager().registerAction(redoAction, "redo");

  connect(undoGroup, &QUndoGroup::cleanChanged, this, &MainWindow::updateWindowTitle);

  connect(getActionManager().findAction("new_project"), &QAction::triggered, this, [this](){
    newProject(Project::Type::Game);
  });
  connect(getActionManager().findAction("clear_recent_projects"), &QAction::triggered, this, &MainWindow::clearRecent);
  connect(getActionManager().findAction("open_project"), &QAction::triggered, this, qOverload<>(&MainWindow::openProject));
  connect(getActionManager().findAction("close_project"), &QAction::triggered, this, &MainWindow::closeProject);
  connect(getActionManager().findAction("settings"), &QAction::triggered, this, &MainWindow::openSettings);
  connect(getActionManager().findAction("export_project"), &QAction::triggered, this, &MainWindow::exportProject);
  connect(getActionManager().findAction("exit"), &QAction::triggered, this, &MainWindow::close);

  connect(getActionManager().findAction("new_scene_document"), &QAction::triggered, this, [this](){
    newDocument(Document::Type::Scene);
  });
  connect(getActionManager().findAction("close_document"), &QAction::triggered, this, &MainWindow::closeDocument);
  connect(getActionManager().findAction("save_document"), &QAction::triggered, this, [this](){
    saveDocument(getDocumentManager().getCurrentDocument());
  });
  connect(getActionManager().findAction("save_document_as"), &QAction::triggered, this, [this](){
    saveDocumentAs(getDocumentManager().getCurrentDocument());
  });
  connect(getActionManager().findAction("save_all_documents"), &QAction::triggered, this, &MainWindow::saveAllDocuments);

  connect(getActionManager().findAction("cut"), &QAction::triggered, this, &MainWindow::performCut);
  connect(getActionManager().findAction("copy"), &QAction::triggered, this, &MainWindow::performCopy);
  connect(getActionManager().findAction("paste"), &QAction::triggered, this, &MainWindow::performPaste);
  connect(getActionManager().findAction("delete"), &QAction::triggered, this, &MainWindow::performDelete);

  connect(getActionManager().findAction("about"), &QAction::triggered, this, &MainWindow::openAbout);

  connect(getActionManager().findMenu("views_and_toolbars"), &QMenu::aboutToShow, this, &MainWindow::updateViewsAndToolbarsMenu);

  connect(&getDocumentManager(), &DocumentManager::currentDocumentChanged, this, &MainWindow::documentChanged);
  connect(&getDocumentManager(), &DocumentManager::documentCloseRequested, this, &MainWindow::closeDocument);

  connect(&getProjectManager(), &ProjectManager::currentProjectChanged, this, &MainWindow::projectChanged);

  connect(&getPreferencesManager(), &PreferencesManager::recentProjectFilesChanged, this, &MainWindow::updateRecentProjectFiles);
}

void MainWindow::retranslateUi() // NOLINT(readability-make-member-function-const)
{
  m_ui->retranslateUi(this);

  getActionManager().findMenu("project")->setTitle(tr("&Project"));
  getActionManager().findMenu("open_recent_project")->setTitle(tr("Open &Recent"));
  getActionManager().findAction("new_project")->setText(tr("&New..."));
  getActionManager().findAction("open_project")->setText(tr("&Open..."));
  getActionManager().findAction("clear_recent_projects")->setText(tr("Clear &Recent"));
  getActionManager().findAction("close_project")->setText(tr("&Close Project"));
  getActionManager().findAction("settings")->setText(tr("&Settings..."));
  getActionManager().findAction("export_project")->setText(tr("&Export..."));
  getActionManager().findAction("exit")->setText(tr("&Exit"));

  getActionManager().findMenu("document")->setTitle(tr("&Document"));
  getActionManager().findMenu("new_document")->setTitle(tr("&New"));
  getActionManager().findAction("new_scene_document")->setText(tr("&Scene..."));
  getActionManager().findAction("close_document")->setText(tr("&Close Document"));
  getActionManager().findAction("save_document")->setText(tr("&Save"));
  getActionManager().findAction("save_document_as")->setText(tr("Save &As"));
  getActionManager().findAction("save_all_documents")->setText(tr("Save All"));

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
