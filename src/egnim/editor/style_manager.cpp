/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QStyleFactory>
/* ----------------------------------- Local -------------------------------- */
#include "style_manager.h"
/* -------------------------------------------------------------------------- */

QScopedPointer<StyleManager> StyleManager::m_instance = QScopedPointer<StyleManager>(nullptr);

StyleManager& StyleManager::getInstance()
{
  if(m_instance.isNull())
    m_instance.reset(new StyleManager);

  return *m_instance;
}

void StyleManager::deleteInstance()
{
  m_instance.reset(nullptr);
}

StyleManager::StyleManager() = default;

StyleManager::~StyleManager() = default;

void StyleManager::unregisterStyle(const QString& style_name)
{
  Q_ASSERT(m_factories.contains(style_name));
  m_factories.erase(style_name);
  Q_EMIT styleUnregistered(style_name);
}

QStringList StyleManager::getAvailableStyles() const
{
  auto available_styles = QStyleFactory::keys();
  for(auto& [name, factory] : m_factories)
    if(!available_styles.contains(name))
      available_styles.push_back(name);

  return available_styles;
}

void StyleManager::setStyle(const QString& style_name)
{
  auto style = m_factories.contains(style_name) ? m_factories[style_name]() : nullptr;
  if(!style) style = QStyleFactory::create(style_name);
  Q_ASSERT(style);

  QApplication::setStyle(style);
  Q_EMIT styleChanged(style_name);
}