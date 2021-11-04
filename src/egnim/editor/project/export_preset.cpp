/* ----------------------------------- Local -------------------------------- */
#include "project/export_preset.h"
#include "project/project.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- ExportPreset ---------------------------- */

ExportPreset::ExportPreset(Type type, Version version, QString name, QString export_path, QObject* parent) :
  QObject(parent),
  m_type(type),
  m_version(version),
  m_name(std::move(name)),
  m_export_path(std::move(export_path))
{

}

ExportPreset::~ExportPreset() = default;

ExportPreset::Type ExportPreset::getType() const
{
  return m_type;
}

void ExportPreset::setVersion(Version version)
{
  m_version = version;
}

ExportPreset::Version ExportPreset::getVersion() const
{
  return m_version;
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

QString ExportPreset::getExecutableExtension() const
{
  return getExecutableExtension(m_type);
}

QString ExportPreset::getExecutableExtension(Type type)
{
  Q_ASSERT(type != Type::Unknown);

  constexpr auto str_types = std::array{
      ".exe",
      "",
      ".app"
  };

  return str_types[static_cast<int>(type)];
}

QString ExportPreset::getExportExecutableName() const
{
  return getExportExecutableName(m_type, m_version);
}

QString ExportPreset::getExportExecutableName(Type type, Version version)
{
  Q_ASSERT(type != Type::Unknown);
  Q_ASSERT(version != Version::Unknown);

  constexpr auto str_types = std::array{
      "windows",
      "linux",
      "mac",
  };

  constexpr auto str_versions = std::array{
      "x32_debug",
      "x32_release",
      "x64_debug",
      "x64_release"
  };

  return QString("%1_%2%3").arg(
      str_types[static_cast<int>(type)],
      str_versions[static_cast<int>(version)],
      getExecutableExtension(type));
}

bool ExportPreset::exportProject(const Project& project) const
{
  // TODO Implementation
  return extendedProjectExport(project);
}

bool ExportPreset::extendedProjectExport(const Project& project) const
{
  return true;
}

void ExportPreset::initializeClone(ExportPreset& export_preset) const
{

}

/* ---------------------------- WindowsExportPreset ------------------------- */

WindowsExportPreset::WindowsExportPreset(QString name, QString export_path, Version version, QObject* parent) :
  ExportPreset(Type::Windows, version, std::move(name), std::move(export_path), parent)
{

}

WindowsExportPreset::~WindowsExportPreset() = default;

std::unique_ptr<ExportPreset> WindowsExportPreset::clone() const
{
  auto windows_export_preset = std::make_unique<WindowsExportPreset>(getName(), getExportPath(), getVersion());
  ExportPreset::initializeClone(*windows_export_preset);

  return windows_export_preset;
}

bool WindowsExportPreset::extendedProjectExport(const Project& project) const
{
  // TODO Implementation
  return true;
}

/* ------------------------------ LinuxExportPreset ------------------------- */

LinuxExportPreset::LinuxExportPreset(QString name, QString export_path, Version version, QObject* parent) :
  ExportPreset(Type::Linux, version, std::move(name), std::move(export_path), parent)
{

}

LinuxExportPreset::~LinuxExportPreset() = default;

std::unique_ptr<ExportPreset> LinuxExportPreset::clone() const
{
  auto linux_export_preset = std::make_unique<LinuxExportPreset>(getName(), getExportPath(), getVersion());
  ExportPreset::initializeClone(*linux_export_preset);

  return linux_export_preset;
}

/* ------------------------------ MacOSExportPreset ------------------------- */

MacOSExportPreset::MacOSExportPreset(QString name, QString export_path, Version version, QObject* parent) :
  ExportPreset(Type::MacOS, version, std::move(name), std::move(export_path), parent)
{

}

MacOSExportPreset::~MacOSExportPreset() = default;

std::unique_ptr<ExportPreset> MacOSExportPreset::clone() const
{
  auto macos_export_preset = std::make_unique<MacOSExportPreset>(getName(), getExportPath(), getVersion());
  ExportPreset::initializeClone(*macos_export_preset);

  return macos_export_preset;
}