#ifndef LOGGING_MANAGER_H
#define LOGGING_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "issue.h"
/* -------------------------------------------------------------------------- */

class LoggingManager : public QObject
{
  Q_OBJECT

public:
  [[nodiscard]] static LoggingManager& getInstance();
  static void deleteInstance();

public:
  ~LoggingManager() override;

  void reportIssue(const Issue& issue);

Q_SIGNALS:
  void onIssueReport(const Issue& issue);

  void onInfoIssueReport(const Issue& issue);
  void onWarningIssueReport(const Issue& issue);
  void onErrorIssueReport(const Issue& issue);

protected:
  explicit LoggingManager();

private:
  static QScopedPointer<LoggingManager> m_instance;
};

inline void REPORT(const Issue& issue)
{
  LoggingManager::getInstance().reportIssue(issue);
}

inline void REPORT(Issue::Severity severity, QString text, Issue::Callback callback = Issue::Callback{})
{
  REPORT(Issue(severity, std::move(text), std::move(callback)));
}

inline void INFO(QString text, Issue::Callback callback = Issue::Callback{})
{
  REPORT(Issue::Severity::Info, std::move(text), std::move(callback));
}

inline void WARNING(QString text, Issue::Callback callback = Issue::Callback{})
{
  REPORT(Issue::Severity::Warning, std::move(text), std::move(callback));
}

inline void ERROR(QString text, Issue::Callback callback = Issue::Callback{})
{
  REPORT(Issue::Severity::Error, std::move(text), std::move(callback));
}

#endif //LOGGING_MANAGER_H
