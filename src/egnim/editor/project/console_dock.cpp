/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QMenu>
#include <QVBoxLayout>
/* ----------------------------------- Local -------------------------------- */
#include "project/console_dock.h"
/* -------------------------------------------------------------------------- */

/* ---------------------------- ConsoleOutputWidget ------------------------- */

class ConsoleOutputWidget : public QPlainTextEdit
{
public:
  using QPlainTextEdit::QPlainTextEdit;

protected:
  void contextMenuEvent(QContextMenuEvent *event) override;
};

void ConsoleOutputWidget::contextMenuEvent(QContextMenuEvent *event)
{
  std::unique_ptr<QMenu> menu { createStandardContextMenu(event->pos()) };

  auto clearIcon = QIcon::fromTheme(QStringLiteral("edit-clear"));
  menu->addSeparator();
  menu->addAction(clearIcon,tr("Clear Console"),
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
  bottomBar->setSpacing(2);

  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->addWidget(m_plain_text_edit);
  layout->addLayout(bottomBar);

  setWidget(widget);

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

void ConsoleDock::retranslateUi()
{
  setWindowTitle(tr("Console"));
}

