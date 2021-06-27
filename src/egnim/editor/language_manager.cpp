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
  m_translations_dir(QLibraryInfo::path(QLibraryInfo::TranslationsPath)),
  m_translations_prefix(QString("app_")),
  m_qt_translator(nullptr),
  m_app_translator(nullptr)
{

}

LanguageManager::~LanguageManager()
{
  if(m_qt_translator)
    QApplication::removeTranslator(m_qt_translator.data());
  if(m_app_translator)
    QApplication::removeTranslator(m_app_translator.data());
}

QStringList LanguageManager::getAvailableLanguages() const
{
  auto languages = QStringList{};
  auto filters = QStringList{m_translations_prefix + QLatin1String("*.qm")};

  QDirIterator iterator(m_translations_dir, filters, QDir::Files | QDir::Readable);
  while(iterator.hasNext())
  {
    iterator.next();
    auto base_name = iterator.fileInfo().completeBaseName();
    languages.append(base_name.mid(m_translations_dir.length()));
  }

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

void LanguageManager::setLanguage(const QString& language)
{
  Q_ASSERT(getAvailableLanguages().contains(language));

  if(m_qt_translator)
    QApplication::removeTranslator(m_qt_translator.data());
  if(m_app_translator)
    QApplication::removeTranslator(m_app_translator.data());

  m_qt_translator.reset(new QTranslator);
  m_app_translator.reset(new QTranslator);

  if(!m_qt_translator->load(QLatin1String("qt_") + language, m_translations_dir))
    m_qt_translator.reset(nullptr);

  if(!m_app_translator->load(m_translations_prefix + language, m_translations_dir))
    m_app_translator.reset(nullptr);

  if(m_qt_translator)
    QApplication::installTranslator(m_qt_translator.data());
  if(m_app_translator)
    QApplication::installTranslator(m_app_translator.data());

  if(m_qt_translator || m_app_translator)
    Q_EMIT languageChanged(language);
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

