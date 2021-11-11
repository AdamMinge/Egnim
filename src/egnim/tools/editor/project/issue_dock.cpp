/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/project/issue_dock.h"
/* -------------------------------------------------------------------------- */

IssueDock::IssueDock(QWidget* parent) :
  QDockWidget(parent)
{
  setObjectName(QLatin1String("Issue"));

  retranslateUi();
}

IssueDock::~IssueDock() = default;

void IssueDock::changeEvent(QEvent* event)
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

void IssueDock::retranslateUi()
{
  setWindowTitle(tr("Issue"));
}