/* ----------------------------------- Local -------------------------------- */
#include "project/export_preset.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- ExportPreset ---------------------------- */

ExportPreset::ExportPreset(Type type, QString name, QObject* parent) :
  QObject(parent),
  m_type(type),
  m_name(std::move(name))
{

}

ExportPreset::~ExportPreset() = default;

ExportPreset::Type ExportPreset::getType() const
{
  return m_type;
}

void ExportPreset::setName(QString name)
{
  m_name = std::move(name);
  Q_EMIT nameChanged(m_name);
}

QString ExportPreset::getName() const
{
  return m_name;
}

void ExportPreset::initializeClone(ExportPreset& export_preset) const
{

}

/* ---------------------------- WindowsExportPreset ------------------------- */

WindowsExportPreset::WindowsExportPreset(QString name, QObject* parent) :
  ExportPreset(Type::Windows, std::move(name), parent)
{

}

WindowsExportPreset::~WindowsExportPreset() = default;

std::unique_ptr<ExportPreset> WindowsExportPreset::clone() const
{
  auto windows_export_preset = std::make_unique<WindowsExportPreset>(getName());
  ExportPreset::initializeClone(*windows_export_preset);

  return windows_export_preset;
}

/* ------------------------------ LinuxExportPreset ------------------------- */

LinuxExportPreset::LinuxExportPreset(QString name, QObject* parent) :
  ExportPreset(Type::Linux, std::move(name), parent)
{

}

LinuxExportPreset::~LinuxExportPreset() = default;

std::unique_ptr<ExportPreset> LinuxExportPreset::clone() const
{
  auto linux_export_preset = std::make_unique<LinuxExportPreset>(getName());
  ExportPreset::initializeClone(*linux_export_preset);

  return linux_export_preset;
}

/* ------------------------------ MacOSExportPreset ------------------------- */

MacOSExportPreset::MacOSExportPreset(QString name, QObject* parent) :
  ExportPreset(Type::MacOS, std::move(name), parent)
{

}

MacOSExportPreset::~MacOSExportPreset() = default;

std::unique_ptr<ExportPreset> MacOSExportPreset::clone() const
{
  auto macos_export_preset = std::make_unique<MacOSExportPreset>(getName());
  ExportPreset::initializeClone(*macos_export_preset);

  return macos_export_preset;
}