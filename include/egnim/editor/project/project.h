#ifndef PROJECT_H
#define PROJECT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QDateTime>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <list>
/* -------------------------------------------------------------------------- */

class Document;

class Project : public QObject
{
  Q_OBJECT

public:
  enum class Type;

public:
  ~Project() override;

  [[nodiscard]] Type getType() const;

  void setFileName(const QString& file_name);
  [[nodiscard]] const QString& getFileName() const;

  [[nodiscard]] QString getDisplayName() const;
  [[nodiscard]] QDateTime getLastModified() const;

  bool save(const QString& file_name);
  static std::unique_ptr<Project> load(const QString& file_name);

  static QString getProjectFileFilter();

  [[nodiscard]] QString getProjectExtension() const;
  static QString getProjectExtension(Type type);

Q_SIGNALS:
  void modifiedChanged();
  void fileNameChanged(const QString& new_file_name, const QString& old_file_name);

  void saved();

protected:
  explicit Project(Type m_type, QObject* parent = nullptr);

private:
  Type m_type;
  QString m_file_name;
};

enum class Project::Type
{
  Game,
  Unknown,
};

#endif //PROJECT_H
