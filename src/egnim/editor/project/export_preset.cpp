/* ----------------------------------- Local -------------------------------- */
#include "project/export_preset.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- ExportPreset ---------------------------- */

ExportPreset::ExportPreset(Type type, QObject* parent) :
  QObject(parent),
  m_type(type)
{

}

ExportPreset::~ExportPreset() = default;

ExportPreset::Type ExportPreset::getType() const
{
  return m_type;
}

/* ---------------------------- WindowsExportPreset ------------------------- */

WindowsExportPreset::WindowsExportPreset(QObject* parent) :
  ExportPreset(Type::Windows, parent)
{

}

WindowsExportPreset::~WindowsExportPreset() = default;

/* ------------------------------ LinuxExportPreset ------------------------- */

LinuxExportPreset::LinuxExportPreset(QObject* parent) :
  ExportPreset(Type::Linux, parent)
{

}

LinuxExportPreset::~LinuxExportPreset() = default;

/* ------------------------------ MacOSExportPreset ------------------------- */

MacOSExportPreset::MacOSExportPreset(QObject* parent) :
  ExportPreset(Type::MacOS, parent)
{

}

MacOSExportPreset::~MacOSExportPreset() = default;