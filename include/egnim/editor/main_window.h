#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QMainWindow>
/* -------------------------------------------------------------------------- */


class MainWindow final : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

};

#endif //MAIN_WINDOW_H
