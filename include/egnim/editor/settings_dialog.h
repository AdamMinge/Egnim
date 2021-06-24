#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* -------------------------------------------------------------------------- */

namespace Ui { class SettingsDialog; }

class SettingsDialog : public QDialog
{
Q_OBJECT

public:
  explicit SettingsDialog(QWidget* parent = nullptr);
  ~SettingsDialog() override;

private:
  QScopedPointer<Ui::SettingsDialog> m_ui;
};

#endif //SETTINGS_DIALOG_H
