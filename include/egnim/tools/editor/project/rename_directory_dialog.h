#ifndef RENAME_DIRECTORY_DIALOG_H
#define RENAME_DIRECTORY_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* -------------------------------------------------------------------------- */

namespace Ui { class RenameDirectoryDialog; }

class RenameDirectoryDialog : public QDialog
{
  Q_OBJECT

public:
  explicit RenameDirectoryDialog(QString dir_name, QWidget* parent = nullptr);
  ~RenameDirectoryDialog() override;

  QString rename();

protected:
  void changeEvent(QEvent* event) override;

private Q_SLOTS:
  void validate();

private:
  void retranslateUi();

private:
  QScopedPointer<Ui::RenameDirectoryDialog> m_ui;
  QString m_dir_name;
};

#endif //RENAME_DIRECTORY_DIALOG_H
