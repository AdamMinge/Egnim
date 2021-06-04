/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/document/scene_dock.h>
/* -------------------------------------------------------------------------- */

SceneDock::SceneDock(QWidget* parent) :
  QDockWidget(parent)
{
  setObjectName(QLatin1String("Scene"));

  retranslateUi();
}

SceneDock::~SceneDock() = default;

void SceneDock::changeEvent(QEvent* event)
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

void SceneDock::retranslateUi()
{
  setWindowTitle(tr("Scene"));
}

