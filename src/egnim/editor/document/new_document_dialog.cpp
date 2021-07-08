/* ----------------------------------- Local -------------------------------- */
#include "document/new_document_dialog.h"
#include "document/scene_document.h"
#include "widgets/file_dialog.h"
#include "project/project_manager.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "document/ui_new_scene_document_dialog.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------- NewDocumentDialog -------------------------- */

NewDocumentDialog::NewDocumentDialog(QWidget* parent) :
  QDialog(parent)
{

}

NewDocumentDialog::~NewDocumentDialog() = default;

std::unique_ptr<Document> NewDocumentDialog::createDocument(Document::Type type, const QString& dir_path)
{
  QScopedPointer<NewDocumentDialog> new_document_dialog(nullptr);
  switch(type)
  {
    case Document::Type::Scene:
      new_document_dialog.reset(new NewSceneDocumentDialog(dir_path));
  }

  if(!new_document_dialog)
    return nullptr;

  return new_document_dialog->create();
}

/* -------------------------- NewSceneDocumentDialog ------------------------ */

NewSceneDocumentDialog::NewSceneDocumentDialog(const QString& dir_path, QWidget* parent) :
  NewDocumentDialog(parent),
  m_ui(new Ui::NewSceneDocumentDialog())
{
  m_ui->setupUi(this);

  connect(m_ui->m_cancel_button, &QPushButton::pressed, this, &QDialog::close);
  connect(m_ui->m_browse_button, &QPushButton::pressed, this, &NewSceneDocumentDialog::onBrowsePressed);
  connect(m_ui->m_create_and_exit_button, &QPushButton::pressed, this, &NewSceneDocumentDialog::accept);

  connect(m_ui->m_document_name_edit, &QLineEdit::textChanged, this, &NewSceneDocumentDialog::validate);
  connect(m_ui->m_document_path_edit, &QLineEdit::textChanged, this, &NewSceneDocumentDialog::validate);

  auto current_project = ProjectManager::getInstance().getProject();
  Q_ASSERT(current_project);
  auto path = dir_path.isEmpty() ? current_project->getDirectory().absolutePath() : dir_path;

  m_ui->m_document_path_edit->setText(path);

  retranslateUi();
  validate();
}

NewSceneDocumentDialog::~NewSceneDocumentDialog() = default;

std::unique_ptr<Document> NewSceneDocumentDialog::create()
{
  if(exec() != QDialog::Accepted)
    return nullptr;

  auto new_document = SceneDocument::create();

  auto document_dir = QDir(m_ui->m_document_path_edit->text());
  auto document_file_name = QString("%1.%2").arg(m_ui->m_document_name_edit->text(), new_document->getDocumentExtension());

  auto document_path = QDir(document_dir).filePath(document_file_name);

  new_document->setFileName(document_path);

  return new_document;
}

void NewSceneDocumentDialog::changeEvent(QEvent* event)
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

void NewSceneDocumentDialog::onBrowsePressed()
{
  auto file_dialog_options =
    QFileDialog::Options() |
    QFileDialog::Option::DontUseNativeDialog |
    QFileDialog::Option::ShowDirsOnly;

  auto current_project = ProjectManager::getInstance().getProject();
  Q_ASSERT(current_project);

  auto dir_path = FileDialog::getExistingDirectory(this,
                                                   tr("New Document"),
                                                   m_ui->m_document_path_edit->text(),
                                                   file_dialog_options,
                                                   current_project->getDirectory().absolutePath());

  if(dir_path.isEmpty())
    return;

  m_ui->m_document_path_edit->setText(dir_path);
}

void NewSceneDocumentDialog::validate()
{
  auto document_dir = QDir(m_ui->m_document_path_edit->text());
  auto document_name = m_ui->m_document_name_edit->text();
  auto name_is_unique = document_dir.entryList(QStringList() << document_name + ".*", QDir::Files).empty();

  auto name_error = document_name.isEmpty() || !name_is_unique;
  auto path_error = !document_dir.exists() || m_ui->m_document_path_edit->text().isEmpty();

  m_ui->m_create_and_exit_button->setDisabled(name_error || path_error);

  m_ui->m_document_name_error_label->setVisible(name_error);
  m_ui->m_document_path_error_label->setVisible(path_error);
}

void NewSceneDocumentDialog::retranslateUi()
{
  m_ui->retranslateUi(this);
}
