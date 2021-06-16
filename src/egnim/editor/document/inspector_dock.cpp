/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/document/inspector_dock.h>
/* -------------------------------------------------------------------------- */

InspectorDock::InspectorDock(QWidget* parent) :
  QDockWidget(parent)
{
  setObjectName(QLatin1String("Inspector"));

  retranslateUi();
}

InspectorDock::~InspectorDock() = default;

void InspectorDock::changeEvent(QEvent* event)
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

void InspectorDock::retranslateUi()
{
  setWindowTitle(tr("Inspector"));
}

