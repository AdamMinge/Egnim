/* ------------------------------------ Qt ---------------------------------- */
#include <QFileDialog>
/* ----------------------------------- Local -------------------------------- */
#include "document/new_document_dialog.h"
#include "document/scene_document.h"
#include "preferences_manager.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "document/ui_new_scene_document_dialog.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct NewDocumentDialog::Preferences
{
  Preference<QString> open_document_start_location = Preference<QString>("document/open_document_start_location", QDir::homePath());
};

/* ----------------------------- NewDocumentDialog -------------------------- */

NewDocumentDialog::NewDocumentDialog(QWidget* parent) :
  QDialog(parent),
  m_preferences(new Preferences)
{

}

NewDocumentDialog::~NewDocumentDialog() = default;

/* -------------------------- NewSceneDocumentDialog ------------------------ */

NewSceneDocumentDialog::NewSceneDocumentDialog(QWidget* parent) :
  NewDocumentDialog(parent),
  m_ui(new Ui::NewSceneDocumentDialog())
{
  m_ui->setupUi(this);

  connect(m_ui->m_cancel_button, &QPushButton::pressed, this, &QDialog::close);
  connect(m_ui->m_browse_button, &QPushButton::pressed, this, &NewSceneDocumentDialog::onBrowsePressed);
  connect(m_ui->m_create_and_exit_button, &QPushButton::pressed, this, &NewSceneDocumentDialog::accept);

  connect(m_ui->m_document_name_edit, &QLineEdit::textChanged, this, &NewSceneDocumentDialog::validate);
  connect(m_ui->m_document_path_edit, &QLineEdit::textChanged, this, &NewSceneDocumentDialog::validate);

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

  auto dir_path = QFileDialog::getExistingDirectory(this,
                                                    tr("New Document"),
                                                    m_preferences->open_document_start_location.get(),
                                                    file_dialog_options);

  if(dir_path.isEmpty())
    return;

  m_preferences->open_document_start_location = dir_path;

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

/* ------------------------------ createDocument ---------------------------- */

std::unique_ptr<Document> createDocument(Document::Type type)
{
  QScopedPointer<NewDocumentDialog> new_document_dialog(nullptr);
  switch(type)
  {
    case Document::Type::Scene:
      new_document_dialog.reset(new NewSceneDocumentDialog);
  }

  if(!new_document_dialog)
    return nullptr;

  return new_document_dialog->create();
}