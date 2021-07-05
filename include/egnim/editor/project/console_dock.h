#ifndef CONSOLE_DOCK_H
#define CONSOLE_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
/* -------------------------------------------------------------------------- */

class ConsoleDock final : public QDockWidget
{
Q_OBJECT

public:
  explicit ConsoleDock(QWidget* parent = nullptr);
  ~ConsoleDock() override;

protected:
  void changeEvent(QEvent* event) override;

private:
  void retranslateUi();
};

#endif //CONSOLE_DOCK_H
