#ifndef EGNIM_ZIP_FILE_H
#define EGNIM_ZIP_FILE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QString>
#include <QStringList>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* -------------------------------------------------------------------------- */

struct zip_t;

class ZipFile : public QObject
{
  Q_OBJECT

public:
  static std::unique_ptr<ZipFile> load(QString file_name, int compression_level = 6);
  static std::unique_ptr<ZipFile> create(QString file_name, int compression_level = 6);

public:
  ~ZipFile() override;

  bool append_entry(const QString& entry_name);
  bool append_entry(const QString& entry_name, const QStringList& entry_names_to_merge);
  bool append_entry(const QString& entry_name, const QByteArray& byteArray);

  bool remove_entry(const QString& entry_name);
  bool remove_entry(const QStringList& entry_names);

  bool extract(const QString& extract_dir);
  bool extract(const QString& entry_name, const QString& extract_entry_name);
  bool extract(const QStringList& entry_names, const QString& extract_dir);

  [[nodiscard]] QStringList getEntryNames() const;
  [[nodiscard]] QString getFileName() const;
  [[nodiscard]] int getCompressionLevel() const;

  [[nodiscard]] bool hasEntryName(const QString& name) const;

protected:
  explicit ZipFile(QString file_name, int compression_level = 6);

private:
  bool execute(char mode, const std::function<bool(zip_t* zip)>& function) const;

private:
  QString m_file_name;
  int m_compression_level;
};

#endif //EGNIM_ZIP_FILE_H
