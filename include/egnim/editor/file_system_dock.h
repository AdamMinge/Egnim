#ifndef FILE_SYSTEM_DOCK_H
#define FILE_SYSTEM_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
/* -------------------------------------------------------------------------- */

class FileSystemDock final : public QDockWidget
{
  Q_OBJECT

public:
  explicit FileSystemDock(QWidget* parent = nullptr);
  ~FileSystemDock() override;

protected:
  void changeEvent(QEvent* event) override;

private:
  void retranslateUi();
};

#endif //FILE_SYSTEM_DOCK_H
