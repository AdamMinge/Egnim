/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "document/nodes_dock.h"
/* -------------------------------------------------------------------------- */

NodesDock::NodesDock(QWidget* parent) :
  QDockWidget(parent)
{
  setObjectName(QLatin1String("Scene"));

  retranslateUi();
}

NodesDock::~NodesDock() = default;

void NodesDock::changeEvent(QEvent* event)
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

void NodesDock::retranslateUi()
{
  setWindowTitle(tr("Nodes"));
}

