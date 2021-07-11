/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
#include <QDir>
/* ----------------------------------- Local -------------------------------- */
#include "project/rename_file_dialog.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_rename_file_dialog.h"
/* -------------------------------------------------------------------------- */

RenameFileDialog::RenameFileDialog(QString file_name, QWidget* parent) :
  QDialog(parent),
  m_ui(new Ui::RenameFileDialog()),
  m_file_name(std::move(file_name))
{
  m_ui->setupUi(this);

  connect(m_ui->m_cancel_button, &QPushButton::pressed, this, &QDialog::close);
  connect(m_ui->m_refactor_button, &QPushButton::pressed, this, &RenameFileDialog::accept);
  connect(m_ui->m_new_name_edit, &QLineEdit::textChanged, this, &RenameFileDialog::validate);

  const auto name = QFileInfo(m_file_name).fileName();

  m_ui->m_new_name_edit->setText(name);
  m_ui->m_new_name_edit->setSelection(0, static_cast<int>(name.lastIndexOf('.')));

  retranslateUi();
  validate();
}

RenameFileDialog::~RenameFileDialog() = default;

QString RenameFileDialog::rename()
{
  if(exec() != QDialog::Accepted)
    return QString();

  const auto file_info = QFileInfo(m_file_name);
  auto dir = file_info.dir();

  auto new_file_name = m_ui->m_new_name_edit->text();
  dir.rename(file_info.fileName(), new_file_name);

  return new_file_name;
}

void RenameFileDialog::changeEvent(QEvent* event)
{
  QDialog::changeEvent(event);

  switch (event->type())
  {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void RenameFileDialog::validate()
{
  const auto new_name = m_ui->m_new_name_edit->text();
  const auto file_info = QFileInfo(m_file_name);
  const auto dir = file_info.dir();

  auto name_is_unique = !new_name.isEmpty() && !dir.exists(new_name);
  m_ui->m_refactor_button->setEnabled(name_is_unique);

  m_ui->m_file_name_error_label->setHidden(name_is_unique);
}

void RenameFileDialog::retranslateUi()
{
  m_ui->retranslateUi(this);

  auto name = QFileInfo(m_file_name).fileName();
  m_ui->m_info_label->setText(tr("Rename file '%1' and its usages to:").arg(name));
}