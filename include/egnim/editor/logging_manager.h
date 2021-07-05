#ifndef LOGGING_MANAGER_H
#define LOGGING_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* -------------------------------------------------------------------------- */

class LoggingManager : public QObject
{
  Q_OBJECT

public:
  [[nodiscard]] static LoggingManager& getInstance();
  static void deleteInstance();

public:
  ~LoggingManager() override;

protected:
  explicit LoggingManager();

private:
  static QScopedPointer<LoggingManager> m_instance;
};

#endif //LOGGING_MANAGER_H
