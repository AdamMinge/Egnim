#ifndef OPEN_PROJECT_DOCK_H
#define OPEN_PROJECT_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
/* -------------------------------------------------------------------------- */

class OpenProjectDock final : public QDockWidget
{
  Q_OBJECT

public:
  explicit OpenProjectDock(QWidget* parent = nullptr);
  ~OpenProjectDock() override;

protected:
  void changeEvent(QEvent* event) override;

private:
  void retranslateUi();
};

#endif //OPEN_PROJECT_DOCK_H
