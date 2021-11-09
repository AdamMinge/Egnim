#ifndef EGNIM_LINE_EDIT_WITH_HISTORY_H
#define EGNIM_LINE_EDIT_WITH_HISTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLineEdit>
#include <QStringList>
/* -------------------------------------------------------------------------- */

class LineEditWithHistory : public QLineEdit
{
  Q_OBJECT

public:
  explicit LineEditWithHistory(QWidget* parent = nullptr);
  ~LineEditWithHistory() override;

public Q_SLOTS:
  void appendToHistory(QString text);

  void setHistory(QStringList history);
  QStringList getHistory() const;

  void move(qsizetype direction);
  void moveNext();
  void movePrev();

private:
  QStringList m_history;
  qsizetype m_history_position;
};

#endif //EGNIM_LINE_EDIT_WITH_HISTORY_H
