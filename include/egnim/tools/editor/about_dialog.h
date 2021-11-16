#ifndef ABOUT_DIALOG_H
#define ABOUT_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* -------------------------------------------------------------------------- */

namespace Ui { class AboutDialog; }

class AboutDialog : public QDialog
{
  Q_OBJECT

public:
  explicit AboutDialog(QWidget* parent = nullptr);
   ~AboutDialog() override;

protected:
  void changeEvent(QEvent* event) override;

private:
  void retranslateUi();

private:
  QScopedPointer<Ui::AboutDialog> m_ui;
};

#endif //ABOUT_DIALOG_H
