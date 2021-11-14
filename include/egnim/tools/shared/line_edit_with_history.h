#ifndef EGNIM_TOOLS_LINE_EDIT_WITH_HISTORY_H
#define EGNIM_TOOLS_LINE_EDIT_WITH_HISTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLineEdit>
#include <QStringList>
/* -------------------------------- Tools Shared ---------------------------- */
#include <egnim/tools/shared/export.h>
/* -------------------------------------------------------------------------- */

namespace tools
{

  class TOOLS_SHARED_API QLineEditWithHistory : public QLineEdit
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

#endif //EGNIM_TOOLS_LINE_EDIT_WITH_HISTORY_H
