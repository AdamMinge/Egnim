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
  [[nodiscard]] const QString& getTranslationsDir() const;
  [[nodiscard]] const QString& getTranslationsPrefix() const;

public Q_SLOTS:
  void setLanguage(const QString& language);
  void setTranslationsDir(const QString& translations_dir);
  void setTranslationsPrefix(const QString& translations_prefix);

Q_SIGNALS:
  void languageChanged(const QString& language);
  void translationsDirChanged(const QString& translations_dir);
  void translationsPrefixChanged(const QString& translations_prefix);

private:
  explicit LanguageManager();

private:
  static QScopedPointer<LanguageManager> m_instance;

  QString m_translations_dir;
  QString m_translations_prefix;
  QScopedPointer<QTranslator> m_qt_translator;
  QScopedPointer<QTranslator> m_app_translator;
};

#endif //LANGUAGE_MANAGER_H
