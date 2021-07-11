/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
#include <QDir>
/* ----------------------------------- Local -------------------------------- */
#include "project/rename_directory_dialog.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_rename_directory_dialog.h"
/* -------------------------------------------------------------------------- */

RenameDirectoryDialog::RenameDirectoryDialog(QString dir_name, QWidget* parent) :
  QDialog(parent),
  m_ui(new Ui::RenameDirectoryDialog()),
  m_dir_name(std::move(dir_name))
{
  m_ui->setupUi(this);

  connect(m_ui->m_cancel_button, &QPushButton::pressed, this, &QDialog::close);
  connect(m_ui->m_refactor_button, &QPushButton::pressed, this, &RenameDirectoryDialog::accept);
  connect(m_ui->m_new_name_edit, &QLineEdit::textChanged, this, &RenameDirectoryDialog::validate);

  const auto file_info = QFileInfo(m_dir_name);
  m_ui->m_new_name_edit->setText(file_info.fileName());
  m_ui->m_new_name_edit->selectAll();

  retranslateUi();
  validate();
}

RenameDirectoryDialog::~RenameDirectoryDialog() = default;

QString RenameDirectoryDialog::rename()
{
  if(exec() != QDialog::Accepted)
    return QString();

  const auto file_info = QFileInfo(m_dir_name);
  auto dir = file_info.dir();

  auto new_file_name = m_ui->m_new_name_edit->text();
  dir.rename(file_info.fileName(), new_file_name);

  return new_file_name;
}

void RenameDirectoryDialog::changeEvent(QEvent* event)
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

void RenameDirectoryDialog::validate()
{
  const auto new_name = m_ui->m_new_name_edit->text();
  const auto file_info = QFileInfo(m_dir_name);
  const auto dir = file_info.dir();

  auto name_is_unique = !new_name.isEmpty() && !dir.exists(new_name);
  m_ui->m_refactor_button->setEnabled(name_is_unique);

  m_ui->m_directory_name_error_label->setHidden(name_is_unique);
}

void RenameDirectoryDialog::retranslateUi()
{
  m_ui->retranslateUi(this);

  auto name = QFileInfo(m_dir_name).fileName();
  m_ui->m_info_label->setText(tr("Rename directory '%1' and its usages to:").arg(name));
}

