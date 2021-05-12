/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/document.h>
/* -------------------------------------------------------------------------- */

Document::Document(Type type, QStringView file_name, QStringView display_name, QObject* parent) :
  QObject(parent),
  m_type(type),
  m_file_name(file_name),
  m_display_name(display_name),
  m_undo_stack(new QUndoStack(this))
{

}

Document::~Document() = default;

Document::Type Document::getType() const
{
  return m_type;
}

QStringView Document::getFileName() const
{
  return m_file_name;
}

QStringView Document::getDisplayName() const
{
  return m_display_name;
}

QUndoStack* Document::getUndoStack() const
{
  return m_undo_stack;
}
