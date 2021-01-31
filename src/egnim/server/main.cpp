//---------------------------- Qt ----------------------------//
#include <QApplication>
//-------------------------- Local ---------------------------//
#include <egnim/server/main_window.h>
#include <egnim/server/meta_types.h>
#include <egnim/config.h>
//------------------------------------------------------------//


int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  QApplication::setApplicationName(QStringLiteral("Egnim-Server"));
  QApplication::setApplicationVersion(QLatin1String(EGNIM_VERSION_STR));
  QApplication::setApplicationDisplayName(QStringLiteral("Egnim-Server"));
  QApplication::setOrganizationName(QStringLiteral("Egnim"));

  registerMetaTypes();

  MainWindow mainWindow;
  mainWindow.show();

  return QApplication::exec();
}