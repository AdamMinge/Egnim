#ifndef EXPORT_PROJECT_DIALOG_H
#define EXPORT_PROJECT_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* -------------------------------------------------------------------------- */

namespace Ui { class ExportProjectDialog; }

class ExportProjectDialog : public QDialog
{
Q_OBJECT

public:
  explicit ExportProjectDialog(QWidget* parent = nullptr);
  ~ExportProjectDialog() override;

protected:
  void changeEvent(QEvent* event) override;

private:
  void retranslateUi();

private:
  QScopedPointer<Ui::ExportProjectDialog> m_ui;
};

#endif //EXPORT_PROJECT_DIALOG_H
