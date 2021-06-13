#ifndef PREFERENCES_MANAGER_H
#define PREFERENCES_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QString>
#include <QSettings>
#include <QScopedPointer>
/* -------------------------------------------------------------------------- */

class PreferencesManager : public QObject
{
  Q_OBJECT

public:
  [[nodiscard]] static PreferencesManager& getInstance();
  static void deleteInstance();

public:
  ~PreferencesManager() override;

  template<typename TYPE> void setValue(const QString& key, const TYPE& value);
  template<typename TYPE> [[nodiscard]] TYPE getValue(const QString& key, const TYPE& default_value = TYPE()) const;

  [[nodiscard]] bool contains(const QString& key);
  void remove(const QString& key);
  void clear();

  [[nodiscard]] QStringList getAllKeys() const;

protected:
  explicit PreferencesManager();

private:
  static QScopedPointer<PreferencesManager> m_instance;

  QSettings m_settings;
};

template<typename TYPE>
void PreferencesManager::setValue(const QString& key, const TYPE& value)
{
  m_settings.setValue(key, value);
}

template<typename TYPE>
TYPE PreferencesManager::getValue(const QString& key, const TYPE& default_value) const
{
  return m_settings.value(key, default_value).template value<TYPE>();
}

template<typename TYPE>
class Preference
{
public:
  explicit Preference(QString key, TYPE default_value = TYPE());

  Preference& operator=(const TYPE& value);

  [[nodiscard]] TYPE get() const;
  void set(const TYPE& value);

  operator TYPE() const; // NOLINT(google-explicit-constructor)

private:
  QString m_key;
  TYPE m_default_value;
};

template<typename TYPE>
Preference<TYPE>::Preference(QString key, TYPE default_value) :
  m_key(std::move(key)),
  m_default_value(default_value)
{

}

template<typename TYPE>
Preference<TYPE>& Preference<TYPE>::operator=(const TYPE& value)
{
  set(value);
  return *this;
}

template<typename TYPE>
TYPE Preference<TYPE>::get() const
{
  return PreferencesManager::getInstance().getValue<TYPE>(m_key, m_default_value);
}

template<typename TYPE>
void Preference<TYPE>::set(const TYPE& value)
{
  PreferencesManager::getInstance().setValue(m_key, value);
}

template<typename TYPE>
Preference<TYPE>::operator TYPE() const
{
  return get();
}

#endif //PREFERENCES_MANAGER_H
