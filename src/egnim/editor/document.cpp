/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/document.h>

#include <utility>
/* -------------------------------------------------------------------------- */

Document::Document(Type type, QString file_name, QString display_name, QObject* parent) :
  QObject(parent),
  m_type(type),
  m_file_name(std::move(file_name)),
  m_display_name(std::move(display_name)),
  m_undo_stack(new QUndoStack(this))
{

}

Document::~Document() = default;

Document::Type Document::getType() const
{
  return m_type;
}

const QString& Document::getFileName() const
{
  return m_file_name;
}

const QString& Document::getDisplayName() const
{
  return m_display_name;
}

QUndoStack* Document::getUndoStack() const
{
  return m_undo_stack;
}
