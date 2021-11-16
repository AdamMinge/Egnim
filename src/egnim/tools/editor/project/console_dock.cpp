/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QMenu>
#include <QShortcut>
#include <QVBoxLayout>
/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/project/console_dock.h"
#include "egnim/tools/editor/logging_manager.h"
/* -------------------------------- Tools Shared ---------------------------- */
#include <egnim/tools/shared/qlineedit/qlineeditwithhistory.h>
#include <egnim/tools/shared/qdpi/qdpiinfo.h>
/* -------------------------------------------------------------------------- */

/* ---------------------------- ConsoleOutputWidget ------------------------- */

void ConsoleOutputWidget::contextMenuEvent(QContextMenuEvent *event)
{
  std::unique_ptr<QMenu> menu { createStandardContextMenu(event->pos()) };

  menu->addSeparator();
  menu->addAction(tr("Clear Console"),
                  this, &QPlainTextEdit::clear);

  menu->exec(event->globalPos());
}

/* -------------------------------- ConsoleDock ----------------------------- */

ConsoleDock::ConsoleDock(QWidget* parent) :
  QDockWidget(parent),
  m_plain_text_edit(new ConsoleOutputWidget()),
  m_line_edit_with_history(new tools::QLineEditWithHistory()),
  m_clear_button(new QPushButton(tr("Clear Console")))
{
  setObjectName(QLatin1String("Scene"));

  m_plain_text_edit->setReadOnly(true);
  auto palette = m_plain_text_edit->palette();
  palette.setColor(QPalette::Base, Qt::black);
  palette.setColor(QPalette::Text, Qt::lightGray);
  m_plain_text_edit->setPalette(palette);

  auto widget = new QWidget(this);
  auto layout = new QVBoxLayout(widget);
  auto bottomBar = new QHBoxLayout();

  bottomBar->addWidget(m_line_edit_with_history);
  bottomBar->addWidget(m_clear_button);
  bottomBar->setSpacing(tools::QDpiInfo::dpiScaled(2));

  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->addWidget(m_plain_text_edit);
  layout->addLayout(bottomBar);

  setWidget(widget);

  auto prev_shortcut = new QShortcut(Qt::Key_Up, m_line_edit_with_history,
                                     nullptr, nullptr, Qt::WidgetShortcut);
  auto next_shortcut = new QShortcut(Qt::Key_Down, m_line_edit_with_history,
                                     nullptr, nullptr, Qt::WidgetShortcut);

  connect(m_line_edit_with_history, &QLineEdit::returnPressed, this, &ConsoleDock::executeScript);
  connect(prev_shortcut, &QShortcut::activated, m_line_edit_with_history, &tools::QLineEditWithHistory::movePrev);
  connect(next_shortcut, &QShortcut::activated, m_line_edit_with_history, &tools::QLineEditWithHistory::moveNext);
  connect(m_clear_button, &QPushButton::pressed, m_plain_text_edit, &QPlainTextEdit::clear);

  auto& logging_manager = LoggingManager::getInstance();
  connect(&logging_manager, &LoggingManager::onInfoIssueReport, this, &ConsoleDock::onInfoIssueReport);
  connect(&logging_manager, &LoggingManager::onWarningIssueReport, this, &ConsoleDock::onWarningIssueReport);
  connect(&logging_manager, &LoggingManager::onErrorIssueReport, this, &ConsoleDock::onErrorIssueReport);

  retranslateUi();
}

ConsoleDock::~ConsoleDock() = default;

void ConsoleDock::changeEvent(QEvent* event)
{
  QDockWidget::changeEvent(event);

  switch (event->type())
  {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void ConsoleDock::onInfoIssueReport(const Issue& issue)
{
  m_plain_text_edit->appendHtml(
      QLatin1String("<pre>") +
      issue.getText().toHtmlEscaped() +
      QLatin1String("</pre>"));
}

void ConsoleDock::onWarningIssueReport(const Issue& issue)
{
  m_plain_text_edit->appendHtml(
      QLatin1String("<pre style='color:orange'>") +
      issue.getText().toHtmlEscaped() +
      QLatin1String("</pre>"));
}

void ConsoleDock::onErrorIssueReport(const Issue& issue)
{
  m_plain_text_edit->appendHtml(
      QLatin1String("<pre style='color:red'>") +
      issue.getText().toHtmlEscaped() +
      QLatin1String("</pre>"));
}

void ConsoleDock::executeScript()
{
  // TODO : implementation //
  m_line_edit_with_history->appendToHistory(m_line_edit_with_history->text());
}

void ConsoleDock::retranslateUi()
{
  setWindowTitle(tr("Console"));
}
