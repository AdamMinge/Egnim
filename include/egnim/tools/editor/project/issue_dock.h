#ifndef EGNIM_ISSUE_DOCK_H
#define EGNIM_ISSUE_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
/* -------------------------------------------------------------------------- */

class IssueDock final : public QDockWidget
{
  Q_OBJECT

public:
  explicit IssueDock(QWidget* parent = nullptr);
  ~IssueDock() override;

protected:
  void changeEvent(QEvent* event) override;

private:
  void retranslateUi();
};

#endif //EGNIM_ISSUE_DOCK_H
