/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QCommandLineParser>
/* ----------------------------------- Local -------------------------------- */
#include "main_window.h"
#include "meta_types.h"
#include "../config.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------- messagesToConsole -------------------------- */

static void messagesToConsole(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
  switch (type)
  {
    case QtInfoMsg:
    case QtDebugMsg:
      // TODO : implementation //
      break;

    case QtWarningMsg:
      // TODO : implementation //
      break;

    case QtCriticalMsg:
      // TODO : implementation //
      break;

    default:
      break;
  }

  static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr);
  (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
}

/* ----------------------------- CommandLineParser -------------------------- */

class CommandLineParser
{
public:
  explicit CommandLineParser();
  ~CommandLineParser() = default;

  void process(const QCoreApplication &app);
};

CommandLineParser::CommandLineParser() = default;

void CommandLineParser::process(const QCoreApplication &app)
{
  QCommandLineParser parser;
  parser.setApplicationDescription("Engine Editor");
  parser.addHelpOption();
  parser.addVersionOption();

  parser.process(app);
}

/* ----------------------------------- main --------------------------------- */

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  QApplication::setApplicationName(QStringLiteral("Egnim-Editor"));
  QApplication::setApplicationVersion(QLatin1String(EGNIM_VERSION_STR));
  QApplication::setApplicationDisplayName(QStringLiteral("Egnim-Editor"));
  QApplication::setOrganizationName(QStringLiteral("Egnim"));

  registerMetaTypes();

  qInstallMessageHandler(messagesToConsole);

  CommandLineParser parser;
  parser.process(app);

  MainWindow mainWindow;
  mainWindow.show();

  return QApplication::exec();
}
