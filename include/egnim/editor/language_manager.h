#ifndef LANGUAGE_MANAGER_H
#define LANGUAGE_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QTranslator>
#include <QScopedPointer>
/* -------------------------------------------------------------------------- */

class LanguageManager : public QObject
{
  Q_OBJECT

public:
  static LanguageManager& getInstance();
  static void deleteInstance();

public:
  ~LanguageManager() override;

  [[nodiscard]] QStringList getAvailableLanguages() const;
  [[nodiscard]] QStringView getTranslationsDir() const;
  [[nodiscard]] QStringView getTranslationsPrefix() const;

public Q_SLOTS:
  void setLanguage(QStringView language);
  void setTranslationsDir(QStringView translations_dir);
  void setTranslationsPrefix(QStringView translations_prefix);

Q_SIGNALS:
  void languageChanged(QStringView language);
  void translationsDirChanged(QStringView translations_dir);
  void translationsPrefixChanged(QStringView translations_prefix);

private:
  explicit LanguageManager();

private:
  static QScopedPointer<LanguageManager> m_instance;

  QStringView m_translations_dir;
  QStringView m_translations_prefix;
  QScopedPointer<QTranslator> m_qt_translator;
  QScopedPointer<QTranslator> m_app_translator;
};

#endif //LANGUAGE_MANAGER_H
