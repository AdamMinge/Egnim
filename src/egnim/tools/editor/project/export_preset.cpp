/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/project/export_preset.h"
#include "egnim/tools/editor/project/project.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- ExportPreset ---------------------------- */

ExportPreset::ExportPreset(Type type, BuildType build_type, BuildVersion build_version,
                           QString name, QString export_path, QObject* parent) :
  QObject(parent),
  m_type(type),
  m_build_type(build_type),
  m_build_version(build_version),
  m_name(std::move(name)),
  m_export_path(std::move(export_path))
{

}

ExportPreset::~ExportPreset() = default;

ExportPreset::Type ExportPreset::getType() const
{
  return m_type;
}

void ExportPreset::setBuildType(BuildType build_type)
{
  m_build_type = build_type;
}

ExportPreset::BuildType ExportPreset::getBuildType() const
{
  return m_build_type;
}

void ExportPreset::setBuildVersion(BuildVersion build_version)
{
  m_build_version = build_version;
}

ExportPreset::BuildVersion ExportPreset::getBuildVersion() const
{
  return m_build_version;
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
  return getExportExecutableName(m_type, m_build_type, m_build_version);
}

QString ExportPreset::getExportExecutableName(Type type, BuildType build_type, BuildVersion build_version)
{
  Q_ASSERT(type != Type::Unknown);

  Q_ASSERT(type != Type::Unknown);

  constexpr auto str_types = std::array{
      "windows",
      "linux",
      "mac",
  };

  constexpr auto str_build_type = std::array{
      "debug",
      "release",
  };

  constexpr auto str_build_versions = std::array{
      "x32"
      "x64"
  };

  return QString("%1_%2_%3%4").arg(
      str_types[static_cast<int>(type)],
      str_build_versions[static_cast<int>(build_version)],
      str_build_type[static_cast<int>(build_type)],
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

WindowsExportPreset::WindowsExportPreset(QString name, QString export_path,
                                         BuildType build_type, BuildVersion build_version, QObject* parent) :
  ExportPreset(Type::Windows, build_type, build_version, std::move(name), std::move(export_path), parent)
{

}

WindowsExportPreset::~WindowsExportPreset() = default;

std::unique_ptr<ExportPreset> WindowsExportPreset::clone() const
{
  auto windows_export_preset = std::make_unique<WindowsExportPreset>(
      getName(), getExportPath(), getBuildType(), getBuildVersion());
  ExportPreset::initializeClone(*windows_export_preset);

  return windows_export_preset;
}

bool WindowsExportPreset::extendedProjectExport(const Project& project) const
{
  // TODO Implementation
  return true;
}

/* ------------------------------ LinuxExportPreset ------------------------- */

LinuxExportPreset::LinuxExportPreset(QString name, QString export_path,
                                     BuildType build_type, BuildVersion build_version, QObject* parent) :
  ExportPreset(Type::Linux, build_type, build_version, std::move(name), std::move(export_path), parent)
{

}

LinuxExportPreset::~LinuxExportPreset() = default;

std::unique_ptr<ExportPreset> LinuxExportPreset::clone() const
{
  auto linux_export_preset = std::make_unique<LinuxExportPreset>(
      getName(), getExportPath(), getBuildType(), getBuildVersion());
  ExportPreset::initializeClone(*linux_export_preset);

  return linux_export_preset;
}

/* ------------------------------ MacOSExportPreset ------------------------- */

MacOSExportPreset::MacOSExportPreset(QString name, QString export_path,
                                     BuildType build_type, BuildVersion build_version, QObject* parent) :
  ExportPreset(Type::MacOS, build_type, build_version, std::move(name), std::move(export_path), parent)
{

}

MacOSExportPreset::~MacOSExportPreset() = default;

std::unique_ptr<ExportPreset> MacOSExportPreset::clone() const
{
  auto macos_export_preset = std::make_unique<MacOSExportPreset>(
      getName(), getExportPath(), getBuildType(), getBuildVersion());
  ExportPreset::initializeClone(*macos_export_preset);

  return macos_export_preset;
}