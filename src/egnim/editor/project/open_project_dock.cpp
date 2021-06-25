/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/open_project_dock.h>
/* -------------------------------------------------------------------------- */

OpenProjectDock::OpenProjectDock(QWidget* parent) :
  QDockWidget(parent)
{
  setObjectName(QLatin1String("Project"));

  retranslateUi();
}

OpenProjectDock::~OpenProjectDock() = default;

void OpenProjectDock::changeEvent(QEvent* event)
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

void OpenProjectDock::retranslateUi()
{
  setWindowTitle(tr("Project"));
}

