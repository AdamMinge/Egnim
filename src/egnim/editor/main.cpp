/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/main_window.h>
#include <egnim/editor/meta_types.h>
#include <egnim/config.h>
/* -------------------------------------------------------------------------- */


int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  QApplication::setApplicationName(QStringLiteral("Egnim-Editor"));
  QApplication::setApplicationVersion(QLatin1String(EGNIM_VERSION_STR));
  QApplication::setApplicationDisplayName(QStringLiteral("Egnim-Editor"));
  QApplication::setOrganizationName(QStringLiteral("Egnim"));
  registerMetaTypes();

  MainWindow mainWindow;
  mainWindow.show();

  return QApplication::exec();
}
