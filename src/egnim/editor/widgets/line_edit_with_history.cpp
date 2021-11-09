/* ----------------------------------- Local -------------------------------- */
#include "widgets/line_edit_with_history.h"
/* -------------------------------------------------------------------------- */

LineEditWithHistory::LineEditWithHistory(QWidget* parent) :
  QLineEdit(parent),
  m_history({}),
  m_history_position(0)
{

}

LineEditWithHistory::~LineEditWithHistory() = default;

void LineEditWithHistory::appendToHistory(QString text)
{
  m_history.append(std::move(text));
  m_history_position = m_history.size();
  clear();
}

void LineEditWithHistory::setHistory(QStringList history)
{
  m_history = (std::move(history));
  m_history_position = m_history.size();
  clear();
}

QStringList LineEditWithHistory::getHistory() const
{
  return m_history;
}

void LineEditWithHistory::move(qsizetype direction)
{
  auto new_history_position = qBound(0, m_history_position + direction, m_history.size());
  if(new_history_position != m_history_position)
  {
    if(new_history_position < m_history.size())
      setText(m_history.at(new_history_position));
    else
      clear();

    m_history_position = new_history_position;
  }
}

void LineEditWithHistory::moveNext()
{
  move(1);
}

void LineEditWithHistory::movePrev()
{
  move(-1);
}
