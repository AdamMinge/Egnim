/* ----------------------------------- Local -------------------------------- */
#include "widgets/file_dialog.h"
#include "project/project_manager.h"
#include "project/new_directory_dialog.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_new_directory_dialog.h"
/* -------------------------------------------------------------------------- */

NewDirectoryDialog::NewDirectoryDialog(const QString& dir_path, QWidget* parent) :
  QDialog(parent),
  m_ui(new Ui::NewDirectoryDialog())
{
  m_ui->setupUi(this);

  connect(m_ui->m_cancel_button, &QPushButton::pressed, this, &QDialog::close);
  connect(m_ui->m_browse_button, &QPushButton::pressed, this, &NewDirectoryDialog::onBrowsePressed);
  connect(m_ui->m_create_and_exit_button, &QPushButton::pressed, this, &NewDirectoryDialog::accept);

  connect(m_ui->m_directory_name_edit, &QLineEdit::textChanged, this, &NewDirectoryDialog::validate);
  connect(m_ui->m_directory_path_edit, &QLineEdit::textChanged, this, &NewDirectoryDialog::validate);

  auto current_project = ProjectManager::getInstance().getProject();
  Q_ASSERT(current_project);
  auto path = dir_path.isEmpty() ? current_project->getDirectory().absolutePath() : dir_path;

  m_ui->m_directory_path_edit->setText(path);

  retranslateUi();
  validate();
}

NewDirectoryDialog::~NewDirectoryDialog() = default;

QDir NewDirectoryDialog::create()
{
  if(exec() != QDialog::Accepted)
    return QDir();

  auto directory_dir = QDir(m_ui->m_directory_path_edit->text());
  const auto directory_name = m_ui->m_directory_name_edit->text();

  if(directory_dir.mkdir(directory_name) && directory_dir.cd(directory_name))
    return directory_dir;

  return  QDir();;
}

void NewDirectoryDialog::changeEvent(QEvent* event)
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

void NewDirectoryDialog::onBrowsePressed()
{
  auto file_dialog_options =
    QFileDialog::Options() |
      QFileDialog::Option::DontUseNativeDialog |
      QFileDialog::Option::ShowDirsOnly;

  auto current_project = ProjectManager::getInstance().getProject();
  Q_ASSERT(current_project);

  auto dir_path = FileDialog::getExistingDirectory(this,
                                                   tr("New Document"),
                                                   m_ui->m_directory_path_edit->text(),
                                                   file_dialog_options,
                                                   current_project->getDirectory().absolutePath());

  if(dir_path.isEmpty())
    return;

  m_ui->m_directory_path_edit->setText(dir_path);
}

void NewDirectoryDialog::validate()
{
  auto directory_dir = QDir(m_ui->m_directory_path_edit->text());
  auto directory_name = m_ui->m_directory_name_edit->text();

  auto name_is_unique = !directory_dir.cd(directory_name);

  auto name_error = directory_name.isEmpty() || !name_is_unique;
  auto path_error = !directory_dir.exists() || m_ui->m_directory_path_edit->text().isEmpty();

  m_ui->m_create_and_exit_button->setDisabled(name_error || path_error);

  m_ui->m_directory_name_error_label->setVisible(name_error);
  m_ui->m_directory_path_error_label->setVisible(path_error);
}

void NewDirectoryDialog::retranslateUi()
{
  m_ui->retranslateUi(this);
}