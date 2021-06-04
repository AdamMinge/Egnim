/* ------------------------------------ Qt ---------------------------------- */
#include <QFileDialog>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/new_project_dialog.h>
#include <egnim/editor/project/project_manager.h>
#include <egnim/editor/project/game_project.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_new_project_dialog.h"
/* -------------------------------------------------------------------------- */

NewProjectDialog::NewProjectDialog(QWidget* parent) :
  QDialog(parent),
  m_ui(new Ui::NewProjectDialog())
{
  m_ui->setupUi(this);

  connect(m_ui->m_cancel_button, &QPushButton::pressed, this, &QDialog::close);
  connect(m_ui->m_browse_button, &QPushButton::pressed, this, &NewProjectDialog::onBrowsePressed);
  connect(m_ui->m_create_and_exit_button, &QPushButton::pressed, this, &NewProjectDialog::onCreateAndExitPressed);

  connect(m_ui->m_project_name_edit, &QLineEdit::textChanged, this, &NewProjectDialog::validate);
  connect(m_ui->m_project_path_edit, &QLineEdit::textChanged, this, &NewProjectDialog::validate);

  validate();
}

NewProjectDialog::~NewProjectDialog() = default;

void NewProjectDialog::onBrowsePressed()
{
  QFileDialog file_dialog;
  file_dialog.setFileMode(QFileDialog::Directory);
  file_dialog.setOption(QFileDialog::ShowDirsOnly);

  if(file_dialog.exec())
    m_ui->m_project_path_edit->setText(file_dialog.directory().path());
}

void NewProjectDialog::onCreateAndExitPressed()
{
  auto project_dir = QDir(m_ui->m_project_path_edit->text());
  auto project_name = m_ui->m_project_name_edit->text();

  auto new_project = GameProject::create(QDir(project_dir).filePath(project_name));
  ProjectManager::getInstance().addProject(std::move(new_project));

  close();
}

void NewProjectDialog::validate()
{
  auto project_dir = QDir(m_ui->m_project_path_edit->text());
  auto project_name = m_ui->m_project_name_edit->text();

  m_ui->m_create_and_exit_button->setEnabled(
    project_dir.exists() && project_dir.isEmpty() && !project_name.isEmpty());

  m_ui->m_project_name_error_label->setVisible(project_name.isEmpty());
  m_ui->m_project_path_error_label->setVisible(!project_dir.exists() || !project_dir.isEmpty());
}
