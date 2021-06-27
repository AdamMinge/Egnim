/* ------------------------------------ Qt ---------------------------------- */
#include <QFileDialog>
/* ----------------------------------- Local -------------------------------- */
#include "project/new_project_dialog.h"
#include "project/game_project.h"
#include "preferences_manager.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_new_game_project_dialog.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct NewProjectDialog::Preferences
{
  Preference<QString> open_project_start_location = Preference<QString>("project/open_project_start_location", QDir::homePath());
};

/* ----------------------------- NewProjectDialog --------------------------- */

NewProjectDialog::NewProjectDialog(QWidget* parent) :
  QDialog(parent),
  m_preferences(new Preferences)
{

}

NewProjectDialog::~NewProjectDialog() = default;

/* --------------------------- NewGameProjectDialog ------------------------- */

NewGameProjectDialog::NewGameProjectDialog(QWidget* parent) :
  NewProjectDialog(parent),
  m_ui(new Ui::NewGameProjectDialog())
{
  m_ui->setupUi(this);

  connect(m_ui->m_cancel_button, &QPushButton::pressed, this, &QDialog::close);
  connect(m_ui->m_browse_button, &QPushButton::pressed, this, &NewGameProjectDialog::onBrowsePressed);
  connect(m_ui->m_create_and_exit_button, &QPushButton::pressed, this, &NewGameProjectDialog::accept);

  connect(m_ui->m_project_name_edit, &QLineEdit::textChanged, this, &NewGameProjectDialog::validate);
  connect(m_ui->m_project_path_edit, &QLineEdit::textChanged, this, &NewGameProjectDialog::validate);

  retranslateUi();
  validate();
}

NewGameProjectDialog::~NewGameProjectDialog() = default;

std::unique_ptr<Project> NewGameProjectDialog::create()
{
  if(exec() != QDialog::Accepted)
    return nullptr;

  auto new_project = GameProject::create();

  auto project_dir = QDir(m_ui->m_project_path_edit->text());
  auto project_file_name = QString("%1.%2").arg(m_ui->m_project_name_edit->text(), new_project->getProjectExtension());
  auto project_path = QDir(project_dir).filePath(project_file_name);

  new_project->setFileName(project_path);

  return new_project;
}

void NewGameProjectDialog::changeEvent(QEvent* event)
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

void NewGameProjectDialog::onBrowsePressed()
{
  auto file_dialog_options =
    QFileDialog::Options() |
    QFileDialog::Option::DontUseNativeDialog |
    QFileDialog::Option::ShowDirsOnly;


  auto dir_path = QFileDialog::getExistingDirectory(this,
                                                    tr("New Project"),
                                                    m_preferences->open_project_start_location.get(),
                                                    file_dialog_options);

  if(dir_path.isEmpty())
    return;

  m_preferences->open_project_start_location = dir_path;

  m_ui->m_project_path_edit->setText(dir_path);
}

void NewGameProjectDialog::validate()
{
  auto project_dir = QDir(m_ui->m_project_path_edit->text());
  auto project_name = m_ui->m_project_name_edit->text();

  auto name_error = project_name.isEmpty();
  auto path_error = !project_dir.exists() || !project_dir.isEmpty();

  m_ui->m_create_and_exit_button->setDisabled(name_error || path_error);

  m_ui->m_project_name_error_label->setVisible(name_error);
  m_ui->m_project_path_error_label->setVisible(path_error);
}

void NewGameProjectDialog::retranslateUi()
{
  m_ui->retranslateUi(this);
}

/* ------------------------------ createProject ----------------------------- */

std::unique_ptr<Project> createProject(Project::Type type)
{
  QScopedPointer<NewProjectDialog> new_project_dialog(nullptr);
  switch(type)
  {
    case Project::Type::Game:
      new_project_dialog.reset(new NewGameProjectDialog);
  }

  if(!new_project_dialog)
    return nullptr;

  return new_project_dialog->create();
}
