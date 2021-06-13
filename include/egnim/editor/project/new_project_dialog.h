#ifndef NEW_PROJECT_DIALOG_H
#define NEW_PROJECT_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* -------------------------------------------------------------------------- */

namespace Ui { class NewProjectDialog; }

class NewProjectDialog : public QDialog
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit NewProjectDialog(QWidget* parent = nullptr);
  ~NewProjectDialog() override;

private Q_SLOTS:
  void onBrowsePressed();
  void onCreateAndExitPressed();

  void validate();

private:
  QScopedPointer<Ui::NewProjectDialog> m_ui;
  QScopedPointer<Preferences> m_preferences;
};

#endif //NEW_PROJECT_DIALOG_H
