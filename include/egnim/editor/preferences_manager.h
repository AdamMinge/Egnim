#ifndef PREFERENCES_MANAGER_H
#define PREFERENCES_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QSettings>
#include <QStringView>
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

  template<typename TYPE> void setValue(QStringView key, const TYPE& value);
  template<typename TYPE> [[nodiscard]] TYPE getValue(QStringView key, const TYPE& default_value = TYPE()) const;

  [[nodiscard]] bool contains(QStringView key);
  void remove(QStringView key);
  void clear();

  [[nodiscard]] QStringList getAllKeys() const;

protected:
  explicit PreferencesManager();

private:
  static QScopedPointer<PreferencesManager> m_instance;

  QSettings m_settings;
};

template<typename TYPE>
void PreferencesManager::setValue(QStringView key, const TYPE& value)
{
  m_settings.setValue(key.toString(), value);
}

template<typename TYPE>
TYPE PreferencesManager::getValue(QStringView key, const TYPE& default_value) const
{
  return m_settings.value(key.toString(), default_value).template value<TYPE>();
}

template<typename TYPE>
class Preference
{
public:
  explicit Preference(QStringView key, TYPE default_value = TYPE());

  Preference& operator=(TYPE&& value);

  [[nodiscard]] TYPE get() const;
  void set(TYPE&& value);

  operator TYPE() const; // NOLINT(google-explicit-constructor)

private:
  QStringView m_key;
  TYPE m_default_value;
};

template<typename TYPE>
Preference<TYPE>::Preference(QStringView key, TYPE default_value) :
  m_key(key),
  m_default_value(default_value)
{

}

template<typename TYPE>
Preference<TYPE>& Preference<TYPE>::operator=(TYPE&& value)
{
  set(std::forward<TYPE>(value));
  return *this;
}

template<typename TYPE>
TYPE Preference<TYPE>::get() const
{
  return PreferencesManager::getInstance().getValue<TYPE>(m_key, m_default_value);
}

template<typename TYPE>
void Preference<TYPE>::set(TYPE&& value)
{
  PreferencesManager::getInstance().setValue(m_key, std::forward<TYPE>(value));
}

template<typename TYPE>
Preference<TYPE>::operator TYPE() const
{
  return get();
}

#endif //PREFERENCES_MANAGER_H
