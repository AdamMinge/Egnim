/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/file_system_dock.h>
/* -------------------------------------------------------------------------- */

FileSystemDock::FileSystemDock(QWidget* parent) :
  QDockWidget(parent)
{
  setObjectName(QLatin1String("FileSystem"));

  retranslateUi();
}

FileSystemDock::~FileSystemDock() = default;

void FileSystemDock::changeEvent(QEvent* event)
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

void FileSystemDock::retranslateUi()
{
  setWindowTitle(tr("File System"));
}

