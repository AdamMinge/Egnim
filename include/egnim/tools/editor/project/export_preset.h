#ifndef EXPORT_PRESET_H
#define EXPORT_PRESET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* -------------------------------------------------------------------------- */

class Project;

class ExportPreset : public QObject
{
  Q_OBJECT

public:
  enum class Type
  {
    Windows,
    Linux,
    MacOS,
    Unknown
  };

  enum class BuildType
  {
    Debug,
    Release
  };

  enum class BuildVersion
  {
    x32,
    x64
  };

public:
  explicit ExportPreset(Type type, BuildType build_type, BuildVersion build_version,
                        QString name, QString export_path, QObject* parent = nullptr);
  ~ExportPreset() override;

  [[nodiscard]] Type getType() const;

  void setBuildType(BuildType build_type);
  [[nodiscard]] BuildType getBuildType() const;

  void setBuildVersion(BuildVersion build_version);
  [[nodiscard]] BuildVersion getBuildVersion() const;

  void setName(QString name);
  [[nodiscard]] QString getName() const;

  void setExportPath(QString path);
  [[nodiscard]] QString getExportPath() const;

  [[nodiscard]] QString getExecutableExtension() const;
  [[nodiscard]] static QString getExecutableExtension(Type type);

  [[nodiscard]] QString getExportExecutableName() const;
  [[nodiscard]] static QString getExportExecutableName(Type type, BuildType build_type, BuildVersion build_version);

  bool exportProject(const Project& project) const; // NOLINT(modernize-use-nodiscard)

  [[nodiscard]] virtual std::unique_ptr<ExportPreset> clone() const = 0;

Q_SIGNALS:
  void nameChanged(const QString& name);
  void exportPathChanged(const QString& name);

protected:
  void initializeClone(ExportPreset& export_preset) const;

  virtual bool extendedProjectExport(const Project& project) const; // NOLINT(modernize-use-nodiscard)

private:
  Type m_type;
  BuildType m_build_type;
  BuildVersion m_build_version;
  QString m_name;
  QString m_export_path;
};

class WindowsExportPreset : public ExportPreset
{
  Q_OBJECT

public:
  explicit WindowsExportPreset(QString name, QString export_path = QString{},
                               BuildType build_type = BuildType::Release,
                               BuildVersion build_version = BuildVersion::x64,
                               QObject* parent = nullptr);
  ~WindowsExportPreset() override;

  [[nodiscard]] std::unique_ptr<ExportPreset> clone() const override;

protected:
  bool extendedProjectExport(const Project& project) const override; // NOLINT(modernize-use-nodiscard)
};

class LinuxExportPreset : public ExportPreset
{
  Q_OBJECT

public:
  explicit LinuxExportPreset(QString name, QString export_path = QString{},
                             BuildType build_type = BuildType::Release,
                             BuildVersion build_version = BuildVersion::x64,
                             QObject* parent = nullptr);
  ~LinuxExportPreset() override;

  [[nodiscard]] std::unique_ptr<ExportPreset> clone() const override;
};

class MacOSExportPreset : public ExportPreset
{
  Q_OBJECT

public:
  explicit MacOSExportPreset(QString name, QString export_path = QString{},
                             BuildType build_type = BuildType::Release,
                             BuildVersion build_version = BuildVersion::x64,
                             QObject* parent = nullptr);
  ~MacOSExportPreset() override;

  [[nodiscard]] std::unique_ptr<ExportPreset> clone() const override;
};

template<typename TYPE>
concept IsExportPreset = std::derived_from<std::decay_t<TYPE>, ExportPreset>;

#endif //EXPORT_PRESET_H
