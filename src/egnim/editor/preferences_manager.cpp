/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/preferences_manager.h>
/* -------------------------------------------------------------------------- */

QScopedPointer<PreferencesManager> PreferencesManager::m_instance = QScopedPointer<PreferencesManager>(nullptr);

PreferencesManager& PreferencesManager::getInstance()
{
  if(m_instance.isNull())
    m_instance.reset(new PreferencesManager);

  return *m_instance;
}

void PreferencesManager::deleteInstance()
{
  m_instance.reset(nullptr);
}

PreferencesManager::PreferencesManager() = default;

PreferencesManager::~PreferencesManager() = default;

bool PreferencesManager::contains(QStringView key)
{
  return m_settings.contains(key.toString());
}

void PreferencesManager::remove(QStringView key)
{
  m_settings.remove(key.toString());
}

void PreferencesManager::clear()
{
  m_settings.clear();
}

QStringList PreferencesManager::getAllKeys() const
{
  return m_settings.allKeys();
}