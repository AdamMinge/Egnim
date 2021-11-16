/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/logging_manager.h"
/* -------------------------------------------------------------------------- */

QScopedPointer<LoggingManager> LoggingManager::m_instance = QScopedPointer<LoggingManager>(nullptr);

LoggingManager& LoggingManager::getInstance()
{
  if(m_instance.isNull())
    m_instance.reset(new LoggingManager);

  return *m_instance;
}

void LoggingManager::deleteInstance()
{
  m_instance.reset(nullptr);
}

LoggingManager::LoggingManager() = default;

LoggingManager::~LoggingManager() = default;

void LoggingManager::reportIssue(const Issue& issue)
{
  onIssueReport(issue);

  switch(issue.getSeverity())
  {
    case Issue::Severity::Info:
      Q_EMIT onInfoIssueReport(issue);
      break;
    case Issue::Severity::Warning:
      Q_EMIT onWarningIssueReport(issue);
      break;
    case Issue::Severity::Error:
      Q_EMIT onErrorIssueReport(issue);
      break;
  }
}