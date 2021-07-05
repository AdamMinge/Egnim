/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "project/console_dock.h"
/* -------------------------------------------------------------------------- */

ConsoleDock::ConsoleDock(QWidget* parent) :
  QDockWidget(parent)
{
  setObjectName(QLatin1String("Scene"));

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

