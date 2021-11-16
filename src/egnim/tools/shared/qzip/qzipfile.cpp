/* ------------------------------------ Qt ---------------------------------- */
#include <QDir>
/* ------------------------------------ Zip --------------------------------- */
#include <zip.h>
/* -------------------------------- Tools Shared ---------------------------- */
#include "egnim/tools/shared/qzip/qzipfile.h"
/* -------------------------------------------------------------------------- */

namespace tools {

#define SAFE_EXECUTE(executor) do { if((executor) < 0) return false; } while(0);

static bool is_zip_valid(const QString& file_name, int compression_level, char mode)
{
  auto zip = zip_open(file_name.toStdString().c_str(), compression_level, mode);
  auto success = static_cast<bool>(zip);
  zip_close(zip);

  return success;
}

std::unique_ptr<QZipFile> QZipFile::load(QString file_name, int compression_level)
{
  if(is_zip_valid(file_name, compression_level, 'r'))
    return std::unique_ptr<QZipFile>(new QZipFile(std::move(file_name), compression_level));
  return nullptr;
}

std::unique_ptr<QZipFile> QZipFile::create(QString file_name, int compression_level)
{
  if(is_zip_valid(file_name, compression_level, 'w'))
    return std::unique_ptr<QZipFile>(new QZipFile(std::move(file_name), compression_level));
  return nullptr;
}

QZipFile::QZipFile(QString file_name, int compression_level) :
  m_file_name(std::move(file_name)),
  m_compression_level(compression_level)
{

}

QZipFile::~QZipFile() = default;

bool QZipFile::append_entry(const QString& entry_name)
{
  return append_entry(entry_name, {entry_name});
}

bool QZipFile::append_entry(const QString& entry_name, const QStringList& entry_names_to_merge)
{
  return execute('a', [&entry_name, &entry_names_to_merge](auto zip){
    SAFE_EXECUTE(zip_entry_open(zip, entry_name.toStdString().c_str()));
    for(const auto& entry_name_to_merge : entry_names_to_merge)
      SAFE_EXECUTE(zip_entry_fwrite(zip, entry_name_to_merge.toStdString().c_str()));
    SAFE_EXECUTE(zip_entry_close(zip));

    return true;
  });
}

bool QZipFile::append_entry(const QString& entry_name, const QByteArray& byteArray)
{
  return execute('a', [&entry_name, &byteArray](auto zip){
    SAFE_EXECUTE(zip_entry_open(zip, entry_name.toStdString().c_str()));
    SAFE_EXECUTE(zip_entry_write(zip, byteArray.data(), byteArray.size()));
    SAFE_EXECUTE(zip_entry_close(zip));

    return true;
  });
}

bool QZipFile::remove_entry(const QString& entry_name)
{
  return execute('d', [&entry_name](auto zip){
    auto str = entry_name.toStdString();
    char* entries[] = { const_cast<char*>(str.c_str()) };
    SAFE_EXECUTE(zip_entries_delete(zip, entries, 1));

    return true;
  });
}

bool QZipFile::remove_entry(const QStringList& entry_names)
{
  auto success = true;
  for(const auto& entry_name : entry_names)
    success &= remove_entry(entry_name);

  return success;
}

bool QZipFile::extract(const QString& extract_dir)
{
  SAFE_EXECUTE(zip_extract(
      m_file_name.toStdString().c_str(),
      extract_dir.toStdString().c_str(), nullptr, nullptr));

  return true;
}

bool QZipFile::extract(const QString& entry_name, const QString& extract_entry_name)
{
  return execute('r', [&entry_name, &extract_entry_name](auto zip){
    SAFE_EXECUTE(zip_entry_open(zip, entry_name.toStdString().c_str()));
    SAFE_EXECUTE(zip_entry_fread(zip, extract_entry_name.toStdString().c_str()));
    SAFE_EXECUTE(zip_entry_close(zip));

    return true;
  });
}

bool QZipFile::extract(const QStringList& entry_names, const QString& extract_dir)
{
  return execute('r', [&entry_names, &extract_dir](auto zip){

    for(const auto& entry_name : entry_names)
    {
      SAFE_EXECUTE(zip_entry_open(zip, entry_name.toStdString().c_str()));
      SAFE_EXECUTE(zip_entry_fread(zip, QDir(extract_dir).filePath(entry_name).toStdString().c_str()));
      SAFE_EXECUTE(zip_entry_close(zip));
    }

    return true;
  });
}

QStringList QZipFile::getEntryNames() const
{
  QStringList entryNames;
  execute('r', [&entryNames](auto zip) {
    auto total_entries = zip_entries_total(zip);
    for(auto i = 0; i < total_entries; ++i)
    {
      SAFE_EXECUTE(zip_entry_openbyindex(zip, i));
      entryNames.append(zip_entry_name(zip));
      SAFE_EXECUTE(zip_entry_close(zip));
    }

    return true;
  });

  return entryNames;
}

QString QZipFile::getFileName() const
{
  return m_file_name;
}

int QZipFile::getCompressionLevel() const
{
  return m_compression_level;
}

bool QZipFile::hasEntryName(const QString& name) const
{
  return getEntryNames().contains(name);
}

bool QZipFile::execute(char mode, const std::function<bool(zip_t* zip)>& function) const
{
  auto zip = zip_open(m_file_name.toStdString().c_str(), m_compression_level, mode);

  auto success = function(zip);
  zip_close(zip);

  return success;
}

} // namespace tools
