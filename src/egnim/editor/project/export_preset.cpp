/* ----------------------------------- Local -------------------------------- */
#include "project/export_preset.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- ExportPreset ---------------------------- */

ExportPreset::ExportPreset(Type type, QString name, QString export_path, QObject* parent) :
  QObject(parent),
  m_type(type),
  m_name(std::move(name)),
  m_export_path(std::move(export_path))
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

void ExportPreset::setExportPath(QString path)
{
  m_export_path = std::move(path);
  Q_EMIT exportPathChanged(m_name);
}

QString ExportPreset::getExportPath() const
{
  return m_export_path;
}

void ExportPreset::initializeClone(ExportPreset& export_preset) const
{

}

/* ---------------------------- WindowsExportPreset ------------------------- */

WindowsExportPreset::WindowsExportPreset(QString name, QString export_path, QObject* parent) :
  ExportPreset(Type::Windows, std::move(name), std::move(export_path), parent)
{

}

WindowsExportPreset::~WindowsExportPreset() = default;

std::unique_ptr<ExportPreset> WindowsExportPreset::clone() const
{
  auto windows_export_preset = std::make_unique<WindowsExportPreset>(getName(), getExportPath());
  ExportPreset::initializeClone(*windows_export_preset);

  return windows_export_preset;
}

/* ------------------------------ LinuxExportPreset ------------------------- */

LinuxExportPreset::LinuxExportPreset(QString name, QString export_path, QObject* parent) :
  ExportPreset(Type::Linux, std::move(name), std::move(export_path), parent)
{

}

LinuxExportPreset::~LinuxExportPreset() = default;

std::unique_ptr<ExportPreset> LinuxExportPreset::clone() const
{
  auto linux_export_preset = std::make_unique<LinuxExportPreset>(getName(), getExportPath());
  ExportPreset::initializeClone(*linux_export_preset);

  return linux_export_preset;
}

/* ------------------------------ MacOSExportPreset ------------------------- */

MacOSExportPreset::MacOSExportPreset(QString name, QString export_path, QObject* parent) :
  ExportPreset(Type::MacOS, std::move(name), std::move(export_path), parent)
{

}

MacOSExportPreset::~MacOSExportPreset() = default;

std::unique_ptr<ExportPreset> MacOSExportPreset::clone() const
{
  auto macos_export_preset = std::make_unique<MacOSExportPreset>(getName(), getExportPath());
  ExportPreset::initializeClone(*macos_export_preset);

  return macos_export_preset;
}