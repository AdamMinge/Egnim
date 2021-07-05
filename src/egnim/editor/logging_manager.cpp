/* ----------------------------------- Local -------------------------------- */
#include "logging_manager.h"
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