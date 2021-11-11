/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/document/document.h"
#include "egnim/tools/editor/document/document_serializer.h"
/* -------------------------------------------------------------------------- */

Document::Document(Type type, QObject* parent) :
  QObject(parent),
  m_type(type),
  m_undo_stack(new QUndoStack(this))
{
  connect(m_undo_stack, &QUndoStack::cleanChanged, this, &Document::modifiedChanged);
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

QString Document::getFileName() const
{
  return m_file_name;
}

QString Document::getDisplayName() const
{
  QString displayName = QFileInfo(m_file_name).fileName();
  if (displayName.isEmpty())
    displayName = tr("untitled.%1").arg(getDocumentExtension());

  return displayName;
}

QDateTime Document::getLastModified() const
{
  return QFileInfo(m_file_name).lastModified();
}

bool Document::isModified() const
{
  return !m_undo_stack->isClean();
}

QUndoStack* Document::getUndoStack() const
{
  return m_undo_stack;
}

bool Document::save(const QString& file_name)
{
  auto serializer = DocumentSerializer();
  auto bytearray = serializer.serialize(*this);

  auto file = QFile(file_name);
  if(!file.open(QIODevice::WriteOnly))
    return false;

  file.write(bytearray);
  file.close();

  getUndoStack()->setClean();
  setFileName(file_name);

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

  auto document = serializer.deserialize(array);
  if(document)
    document->setFileName(file_name);

  return document;
}

QString Document::getDocumentFileFilter()
{
  auto filter = QString{};

  filter.append(tr("Scene Document (*.%1)").arg(getDocumentExtension(Type::Scene)));

  return filter;
}

QString Document::getDocumentExtension() const
{
  return getDocumentExtension(m_type);
}


QString Document::getDocumentExtension(Type type)
{
  switch(type)
  {
    case Type::Scene:
      return "egn-scene";
  }

  return QString{};
}

QStringList Document::getDocumentExtensions()
{
  auto extensions = QStringList();

  extensions << getDocumentExtension(Type::Scene);

  return extensions;
}
