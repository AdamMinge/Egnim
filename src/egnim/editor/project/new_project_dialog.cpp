/* ------------------------------------ Qt ---------------------------------- */
#include <QFileDialog>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/new_project_dialog.h>
#include <egnim/editor/project/project_manager.h>
#include <egnim/editor/project/game_project.h>
#include <egnim/editor/preferences_manager.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_new_project_dialog.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct NewProjectDialog::Preferences
{
  Preference<QString> open_project_start_location = Preference<QString>("project/open_project_start_location", QDir::homePath());
};

/* ----------------------------- NewProjectDialog --------------------------- */

NewProjectDialog::NewProjectDialog(QWidget* parent) :
  QDialog(parent),
  m_ui(new Ui::NewProjectDialog()),
  m_preferences(new Preferences)
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
  auto dir_path = QFileDialog::getExistingDirectory(this,
                                                    tr("New Project"),
                                                    m_preferences->open_project_start_location.get(),
                                                    QFileDialog::Options() | QFileDialog::Option::DontUseNativeDialog);

  if(dir_path.isEmpty())
    return;

  m_preferences->open_project_start_location = dir_path;

  m_ui->m_project_path_edit->setText(dir_path);
}

void NewProjectDialog::onCreateAndExitPressed()
{
  auto new_project = GameProject::create();

  auto project_dir = QDir(m_ui->m_project_path_edit->text());
  auto project_file_name = m_ui->m_project_name_edit->text() + new_project->getProjectExtension();

  new_project->save(QDir(project_dir).filePath(project_file_name));

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
