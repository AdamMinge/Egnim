#ifndef EGNIM_LINE_EDIT_WITH_HISTORY_H
#define EGNIM_LINE_EDIT_WITH_HISTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLineEdit>
#include <QStringList>
/* -------------------------------------------------------------------------- */

namespace tools
{

  class QLineEditWithHistory : public QLineEdit
  {
  Q_OBJECT

  public:
    explicit QLineEditWithHistory(QWidget* parent = nullptr);
    ~QLineEditWithHistory() override;

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

} // namespace tools

#endif //EGNIM_LINE_EDIT_WITH_HISTORY_H
