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
  explicit ExportPreset(Type type, QString name, QObject* parent = nullptr);
  ~ExportPreset() override;

  [[nodiscard]] Type getType() const;

  void setName(QString name);
  [[nodiscard]] QString getName() const;

  [[nodiscard]] virtual std::unique_ptr<ExportPreset> clone() const = 0;

Q_SIGNALS:
  void nameChanged(const QString& name);

protected:
  void initializeClone(ExportPreset& export_preset) const;

private:
  Type m_type;
  QString m_name;
};

class WindowsExportPreset : public ExportPreset
{
  Q_OBJECT

public:
  explicit WindowsExportPreset(QString name, QObject* parent = nullptr);
  ~WindowsExportPreset() override;

  [[nodiscard]] std::unique_ptr<ExportPreset> clone() const override;
};

class LinuxExportPreset : public ExportPreset
{
  Q_OBJECT

public:
  explicit LinuxExportPreset(QString name, QObject* parent = nullptr);
  ~LinuxExportPreset() override;

  [[nodiscard]] std::unique_ptr<ExportPreset> clone() const override;
};

class MacOSExportPreset : public ExportPreset
{
  Q_OBJECT

public:
  explicit MacOSExportPreset(QString name, QObject* parent = nullptr);
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
