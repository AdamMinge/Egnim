//---------------------------- Qt ----------------------------//
#include <QApplication>
//-------------------------- Local ---------------------------//
#include <egnim/client-listener/main_window.h>
#include <egnim/client-listener/meta_types.h>
#include <egnim/config.h>
//------------------------------------------------------------//


int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  QApplication::setApplicationName(QStringLiteral("Egnim-Listner"));
  QApplication::setApplicationVersion(QLatin1String(EGNIM_VERSION_STR));
  QApplication::setApplicationDisplayName(QStringLiteral("Egnim-Listner"));
  QApplication::setOrganizationName(QStringLiteral("Egnim"));
  registerMetaTypes();

  MainWindow mainWindow;
  mainWindow.show();

  return QApplication::exec();
}
