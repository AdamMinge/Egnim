/* ------------------------------------ Qt ---------------------------------- */
#include <QCloseEvent>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/main_window.h>
#include <egnim/editor/preferences_manager.h>
#include <egnim/editor/document_manager.h>
#include <egnim/editor/language_manager.h>
#include <egnim/editor/action_manager.h>
#include <egnim/editor/style_manager.h>
#include <egnim/editor/game_editor.h>
#include <egnim/editor/new_project_dialog.h>
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
  m_current_document(nullptr)
{
  m_ui->setupUi(this);

  registerMenus();
  registerActions();

  getDocumentManager().addEditor(Document::Type::Game, std::make_unique<GameEditor>());

  setCentralWidget(getDocumentManager().getWidget());

  connect(getActionManager().findAction("new_project"), &QAction::triggered, this, &MainWindow::newProject);
  connect(getActionManager().findAction("open_project"), &QAction::triggered, this, &MainWindow::openProject);
  connect(getActionManager().findAction("exit"), &QAction::triggered, this, &MainWindow::close);

  connect(&getDocumentManager(), &DocumentManager::documentCloseRequested, this, &MainWindow::closeDocument);
  connect(&getDocumentManager(), &DocumentManager::currentDocumentChanged, this, &MainWindow::documentChanged);

  readSettings();
  retranslateUi();
}

MainWindow::~MainWindow()
{
  getDocumentManager().removeAllDocuments();
  getDocumentManager().removeAllEditors();

  DocumentManager::deleteInstance();
  LanguageManager::deleteInstance();
  ActionManager::deleteInstance();
  StyleManager::deleteInstance();
  PreferencesManager::deleteInstance();
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

Document* MainWindow::getCurrentDocument() const
{
  return m_current_document;
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

void MainWindow::closeDocument(int index)
{
  if (confirmSave(getDocumentManager().getDocument(index)))
    getDocumentManager().removeDocument(index);
}

void MainWindow::documentChanged(Document* document)
{
  m_current_document = document;
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

bool MainWindow::confirmSave(Document* document)
{
  // TODO : implementation //
  return true;
}

bool MainWindow::confirmAllSave()
{
  // TODO : implementation //
  return true;
}

void MainWindow::writeSettings()
{
  m_preferences->main_window_geometry = saveGeometry();
  m_preferences->main_window_state = saveState();

  getDocumentManager().saveState();
}

void MainWindow::readSettings()
{
  auto main_window_geometry = static_cast<QByteArray>(m_preferences->main_window_geometry);
  auto main_window_state = static_cast<QByteArray>(m_preferences->main_window_state);

  if(!main_window_geometry.isNull())
    restoreGeometry(main_window_geometry);

  if(!main_window_state.isNull())
    restoreState(main_window_state);

  getDocumentManager().restoreState();
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
  getActionManager().registerAction(m_ui->m_action_save_as, "save_as");
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

