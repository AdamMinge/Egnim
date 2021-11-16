#ifndef RENAME_FILE_DIALOG_H
#define RENAME_FILE_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* -------------------------------------------------------------------------- */

namespace Ui { class RenameFileDialog; }

class RenameFileDialog : public QDialog
{
  Q_OBJECT

public:
  explicit RenameFileDialog(QString file_name, QWidget* parent = nullptr);
  ~RenameFileDialog() override;

  QString rename();

protected:
  void changeEvent(QEvent* event) override;

private Q_SLOTS:
  void validate();

private:
  void retranslateUi();

private:
  QScopedPointer<Ui::RenameFileDialog> m_ui;
  QString m_file_name;
};

#endif //RENAME_FILE_DIALOG_H
