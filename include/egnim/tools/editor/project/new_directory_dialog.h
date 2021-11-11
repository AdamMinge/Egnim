#ifndef NEW_DIRECTORY_DIALOG_H
#define NEW_DIRECTORY_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* -------------------------------------------------------------------------- */

namespace Ui { class NewDirectoryDialog; }

class NewDirectoryDialog : public QDialog
{
  Q_OBJECT

public:
  explicit NewDirectoryDialog(const QString& dir_path = QString(), QWidget* parent = nullptr);
  ~NewDirectoryDialog() override;

  QDir create();

protected:
  void changeEvent(QEvent* event) override;

private Q_SLOTS:
  void onBrowsePressed();
  void validate();

private:
  void retranslateUi();

private:
  QScopedPointer<Ui::NewDirectoryDialog> m_ui;
};

#endif //NEW_DIRECTORY_DIALOG_H
