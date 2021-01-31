#ifndef EGNIM_MAIN_WINDOW_H
#define EGNIM_MAIN_WINDOW_H

//--------------------------- Qt ----------------------------//
#include <QMainWindow>
//-----------------------------------------------------------//


class MainWindow final : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

};

#endif //EGNIM_MAIN_WINDOW_H
