/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/document/document.h>
/* -------------------------------------------------------------------------- */

Document::Document(Type type, QString file_name, QObject* parent) :
  QObject(parent),
  m_type(type),
  m_file_name(std::move(file_name)),
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

const QString& Document::getFileName() const
{
  return m_file_name;
}

QString Document::getDisplayName() const
{
  QString displayName = QFileInfo(m_file_name).fileName();
  if (displayName.isEmpty())
    displayName = tr("untitled.egn");

  return displayName;
}

QUndoStack* Document::getUndoStack() const
{
  return m_undo_stack;
}

bool Document::isModified() const
{
  return !m_undo_stack->isClean();
}
