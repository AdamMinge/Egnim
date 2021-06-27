/* ------------------------------------ Qt ---------------------------------- */
#include <QLibraryInfo>
#include <QApplication>
#include <QDirIterator>
/* ----------------------------------- Local -------------------------------- */
#include "language_manager.h"
/* -------------------------------------------------------------------------- */

QScopedPointer<LanguageManager> LanguageManager::m_instance = QScopedPointer<LanguageManager>(nullptr);

LanguageManager& LanguageManager::getInstance()
{
  if(m_instance.isNull())
    m_instance.reset(new LanguageManager);

  return *m_instance;
}

void LanguageManager::deleteInstance()
{
  m_instance.reset(nullptr);
}

LanguageManager::LanguageManager() :
  m_translations_dir(":/translations"),
  m_translations_prefix(QString("egnim_editor_")),
  m_qt_translator(nullptr),
  m_app_translator(nullptr),
  m_current_locale(QLocale(QLocale::Language::English))
{

}

LanguageManager::~LanguageManager()
{
  if(m_qt_translator)
    QApplication::removeTranslator(m_qt_translator.data());
  if(m_app_translator)
    QApplication::removeTranslator(m_app_translator.data());
}

QList<QLocale> LanguageManager::getAvailableLanguages() const
{
  auto languages = QList<QLocale>{};
  auto filters = QStringList{m_translations_prefix + QLatin1String("*.qm")};

  QDirIterator iterator(m_translations_dir, filters, QDir::Files | QDir::Readable);
  while(iterator.hasNext())
  {
    iterator.next();
    auto base_name = iterator.fileInfo().completeBaseName();
    languages.append(QLocale(base_name.mid(m_translations_prefix.length())));
  }

  if(languages.empty())
    languages.append(m_current_locale);

  return languages;
}

const QString& LanguageManager::getTranslationsDir() const
{
  return m_translations_dir;
}

const QString& LanguageManager::getTranslationsPrefix() const
{
  return m_translations_prefix;
}

QLocale LanguageManager::getCurrentLanguage() const
{
  return m_current_locale;
}

bool LanguageManager::setLanguage(const QLocale& locale)
{
  Q_ASSERT(getAvailableLanguages().contains(locale));
  auto bcp47_name = locale.bcp47Name();

  if(m_qt_translator)
    QApplication::removeTranslator(m_qt_translator.data());
  if(m_app_translator)
    QApplication::removeTranslator(m_app_translator.data());

  m_qt_translator.reset(new QTranslator);
  m_app_translator.reset(new QTranslator);

  if(!m_qt_translator->load(QLatin1String("qt_%1").arg(bcp47_name), m_translations_dir) ||
     !m_app_translator->load(m_translations_prefix + bcp47_name, m_translations_dir))
  {
    m_qt_translator.reset(nullptr);
    m_app_translator.reset(nullptr);
    return false;
  }

  m_current_locale = locale;
  QApplication::installTranslator(m_qt_translator.data());
  QApplication::installTranslator(m_app_translator.data());
  Q_EMIT languageChanged(locale);
  return true;
}

void LanguageManager::setTranslationsDir(const QString& translations_dir)
{
  m_translations_dir = translations_dir;
  Q_EMIT translationsDirChanged(translations_dir);
}

void LanguageManager::setTranslationsPrefix(const QString& translations_prefix)
{
  m_translations_prefix = translations_prefix;
  Q_EMIT translationsPrefixChanged(translations_prefix);
}
