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
  m_preferences_manager(PreferencesManager::getInstance()),
  m_document_manager(DocumentManager::getInstance()),
  m_language_manager(LanguageManager::getInstance()),
  m_action_manager(ActionManager::getInstance()),
  m_style_manager(StyleManager::getInstance()),
  m_preferences(new Preferences),
  m_current_document(nullptr)
{
  m_ui->setupUi(this);

  m_document_manager.addEditor(Document::Type::Game, std::make_unique<GameEditor>());

  setCentralWidget(m_document_manager.getWidget());

  connect(&m_document_manager, &DocumentManager::documentCloseRequested, this, &MainWindow::closeDocument);
  connect(&m_document_manager, &DocumentManager::currentDocumentChanged, this, &MainWindow::documentChanged);

  readSettings();
  retranslateUi();
}

MainWindow::~MainWindow()
{
  m_document_manager.removeAllDocuments();
  m_document_manager.removeAllEditors();

  DocumentManager::deleteInstance();
  LanguageManager::deleteInstance();
  ActionManager::deleteInstance();
  StyleManager::deleteInstance();
  PreferencesManager::deleteInstance();
}

DocumentManager& MainWindow::getDocumentManager() const
{
  return m_document_manager;
}

LanguageManager& MainWindow::getLanguageManager() const
{
  return m_language_manager;
}

StyleManager& MainWindow::getStyleManager() const
{
  return m_style_manager;
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
  if (confirmSave(m_document_manager.getDocument(index)))
    m_document_manager.removeDocument(index);
}

void MainWindow::documentChanged(Document* document)
{
  m_current_document = document;
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

  m_document_manager.saveState();
}

void MainWindow::readSettings()
{
  auto main_window_geometry = static_cast<QByteArray>(m_preferences->main_window_geometry);
  auto main_window_state = static_cast<QByteArray>(m_preferences->main_window_state);

  if(!main_window_geometry.isNull())
    restoreGeometry(main_window_geometry);

  if(!main_window_state.isNull())
    restoreState(main_window_state);

  m_document_manager.restoreState();
}

void MainWindow::retranslateUi()
{
  // TODO : implementation //
}

