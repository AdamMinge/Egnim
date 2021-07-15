#ifndef EXPORT_PRESET_H
#define EXPORT_PRESET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* -------------------------------------------------------------------------- */

class ExportPreset : public QObject
{
  Q_OBJECT

public:
  enum class Type;

public:
  explicit ExportPreset(Type type, QObject* parent = nullptr);
  ~ExportPreset() override;

  [[nodiscard]] Type getType() const;

private:
  Type m_type;
};

class WindowsExportPreset : public ExportPreset
{
  Q_OBJECT

public:
  explicit WindowsExportPreset(QObject* parent = nullptr);
  ~WindowsExportPreset() override;
};

class LinuxExportPreset : public ExportPreset
{
  Q_OBJECT

public:
  explicit LinuxExportPreset(QObject* parent = nullptr);
  ~LinuxExportPreset() override;
};

class MacOSExportPreset : public ExportPreset
{
  Q_OBJECT

public:
  explicit MacOSExportPreset(QObject* parent = nullptr);
  ~MacOSExportPreset() override;
};

enum class ExportPreset::Type
{
  Windows,
  Linux,
  MacOS
};

#endif //EXPORT_PRESET_H
