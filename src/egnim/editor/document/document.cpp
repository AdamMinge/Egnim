/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/document/document.h>
#include <egnim/editor/document/document_serializer.h>
/* -------------------------------------------------------------------------- */

Document::Document(Type type, QString file_name, QObject* parent) :
  QObject(parent),
  m_type(type),
  m_file_name(std::move(file_name))
{

}

Document::~Document() = default;

Document::Type Document::getType() const
{
  return m_type;
}

void Document::setFileName(const QString& file_name)
{
  if(m_file_name == file_name)
    return;

  auto old_file_name = m_file_name;
  m_file_name = file_name;

  Q_EMIT fileNameChanged(file_name, old_file_name);
}

const QString& Document::getFileName() const
{
  return m_file_name;
}

QString Document::getDisplayName() const
{
  QString displayName = QFileInfo(m_file_name).fileName();
  return displayName;
}

bool Document::save(const QString& file_name)
{
  auto serializer = DocumentSerializer();
  auto bytearray = serializer.serialize(*this);

  auto file = QFile(m_file_name);
  if(!file.open(QIODevice::WriteOnly))
    return false;

  file.write(bytearray);
  file.close();

  Q_EMIT saved();
  return true;
}

std::unique_ptr<Document> Document::load(const QString& file_name)
{
  auto file = QFile(file_name);
  if(!file.open(QIODevice::ReadOnly))
    return nullptr;

  auto array = file.readAll();
  auto serializer = DocumentSerializer();

  return serializer.deserialize(array);
}
