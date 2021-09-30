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
  explicit ExportPreset(Type type, QString name, QString export_path, QObject* parent = nullptr);
  ~ExportPreset() override;

  [[nodiscard]] Type getType() const;

  void setName(QString name);
  [[nodiscard]] QString getName() const;

  void setExportPath(QString path);
  [[nodiscard]] QString getExportPath() const;

  [[nodiscard]] virtual std::unique_ptr<ExportPreset> clone() const = 0;

Q_SIGNALS:
  void nameChanged(const QString& name);
  void exportPathChanged(const QString& name);

protected:
  void initializeClone(ExportPreset& export_preset) const;

private:
  Type m_type;
  QString m_name;
  QString m_export_path;
};

class WindowsExportPreset : public ExportPreset
{
  Q_OBJECT

public:
  explicit WindowsExportPreset(QString name, QString export_path = QString{}, QObject* parent = nullptr);
  ~WindowsExportPreset() override;

  [[nodiscard]] std::unique_ptr<ExportPreset> clone() const override;
};

class LinuxExportPreset : public ExportPreset
{
  Q_OBJECT

public:
  explicit LinuxExportPreset(QString name, QString export_path = QString{}, QObject* parent = nullptr);
  ~LinuxExportPreset() override;

  [[nodiscard]] std::unique_ptr<ExportPreset> clone() const override;
};

class MacOSExportPreset : public ExportPreset
{
  Q_OBJECT

public:
  explicit MacOSExportPreset(QString name, QString export_path = QString{}, QObject* parent = nullptr);
  ~MacOSExportPreset() override;

  [[nodiscard]] std::unique_ptr<ExportPreset> clone() const override;
};

enum class ExportPreset::Type
{
  Windows,
  Linux,
  MacOS,
  Unknown
};

#endif //EXPORT_PRESET_H
