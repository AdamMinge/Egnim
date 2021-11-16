#ifndef EGNIM_TOOLS_ZIP_FILE_H
#define EGNIM_TOOLS_ZIP_FILE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QString>
#include <QStringList>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* -------------------------------- Tools Shared ---------------------------- */
#include <egnim/tools/shared/export.h>
/* -------------------------------------------------------------------------- */

struct zip_t;

namespace tools
{

  class TOOLS_SHARED_API QZipFile : public QObject
  {
    Q_OBJECT

  public:
    static std::unique_ptr<QZipFile> load(QString file_name, int compression_level = 6);
    static std::unique_ptr<QZipFile> create(QString file_name, int compression_level = 6);

  public:
    ~QZipFile() override;

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
    explicit QZipFile(QString file_name, int compression_level = 6);

  private:
    bool execute(char mode, const std::function<bool(zip_t* zip)>& function) const;

  private:
    QString m_file_name;
    int m_compression_level;
  };

}

#endif //EGNIM_TOOLS_ZIP_FILE_H
