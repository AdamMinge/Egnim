/* -------------------------------- Tools Shared ---------------------------- */
#include "egnim/tools/shared/qlineedit/qlineeditwithhistory.h"
/* -------------------------------------------------------------------------- */

namespace tools {

QLineEditWithHistory::QLineEditWithHistory(QWidget* parent) :
  QLineEdit(parent),
  m_history({}),
  m_history_position(0)
{

}

QLineEditWithHistory::~QLineEditWithHistory() = default;

void QLineEditWithHistory::appendToHistory(QString text)
{
  m_history.append(std::move(text));
  m_history_position = m_history.size();
  clear();
}

void QLineEditWithHistory::setHistory(QStringList history)
{
  m_history = (std::move(history));
  m_history_position = m_history.size();
  clear();
}

QStringList QLineEditWithHistory::getHistory() const
{
  return m_history;
}

void QLineEditWithHistory::move(qsizetype direction)
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

void QLineEditWithHistory::moveNext()
{
  move(1);
}

void QLineEditWithHistory::movePrev()
{
  move(-1);
}

} // namespace tools
