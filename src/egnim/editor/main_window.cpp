/* ------------------------------------ Qt ---------------------------------- */
#include <QCloseEvent>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/main_window.h>
#include <egnim/editor/document_manager.h>
#include <egnim/editor/language_manager.h>
#include <egnim/editor/style_manager.h>
/* -------------------------------------------------------------------------- */



MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_document_manager(DocumentManager::getInstance()),
  m_language_manager(LanguageManager::getInstance()),
  m_style_manager(StyleManager::getInstance()),
  m_current_document(nullptr)
{
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
  StyleManager::deleteInstance();
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
  m_document_manager.saveState();
}

void MainWindow::readSettings()
{
  m_document_manager.restoreState();
}

void MainWindow::retranslateUi()
{
  // TODO : implementation //
}

