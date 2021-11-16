#ifndef PROJECT_H
#define PROJECT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDir>
#include <QObject>
#include <QDateTime>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <list>
/* -------------------------------------------------------------------------- */

class ExportPresetListModel;

class Project : public QObject
{
  Q_OBJECT

public:
  enum class Type;

public:
  ~Project() override;

  [[nodiscard]] Type getType() const;

  void setFileName(const QString& file_name);
  [[nodiscard]] QString getFileName() const;
  [[nodiscard]] QDir getDirectory() const;

  [[nodiscard]] QString getDisplayName() const;
  [[nodiscard]] QDateTime getLastModified() const;

  bool save(const QString& file_name);
  static std::unique_ptr<Project> load(const QString& file_name);

  static QString getProjectFileFilter();
  static QStringList projectSupportedFormats();

  [[nodiscard]] QString getProjectExtension() const;
  static QString getProjectExtension(Type type);

  [[nodiscard]] ExportPresetListModel* getExportPresetModel() const;

Q_SIGNALS:
  void modifiedChanged();
  void fileNameChanged(const QString& new_file_name, const QString& old_file_name);

  void saved();

protected:
  explicit Project(Type m_type, QObject* parent = nullptr);

private:
  Type m_type;
  QString m_file_name;
  ExportPresetListModel* m_export_preset_model;
};

enum class Project::Type
{
  Game,
  Unknown,
};

#endif //PROJECT_H
