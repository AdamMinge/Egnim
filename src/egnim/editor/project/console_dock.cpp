/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QMenu>
#include <QVBoxLayout>
/* ----------------------------------- Local -------------------------------- */
#include "project/console_dock.h"
#include "utils/dpi_info.h"
#include "logging_manager.h"
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
  m_line_edit(new QLineEdit()),
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

  bottomBar->addWidget(m_line_edit);
  bottomBar->addWidget(m_clear_button);
  bottomBar->setSpacing(DpiInfo::dpiScaled(2));

  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->addWidget(m_plain_text_edit);
  layout->addLayout(bottomBar);

  setWidget(widget);

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

void ConsoleDock::retranslateUi()
{
  setWindowTitle(tr("Console"));
}

