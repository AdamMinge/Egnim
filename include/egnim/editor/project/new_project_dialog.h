#ifndef NEW_PROJECT_DIALOG_H
#define NEW_PROJECT_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/project.h>
/* -------------------------------------------------------------------------- */

namespace Ui { class NewGameProjectDialog; }

class NewProjectDialog : public QDialog
{
  Q_OBJECT

private:
  struct Preferences;

public:
  ~NewProjectDialog() override;

  [[nodiscard]] virtual std::unique_ptr<Project> create() = 0;

protected:
  explicit NewProjectDialog(QWidget* parent = nullptr);

protected:
  QScopedPointer<Preferences> m_preferences;
};

class NewGameProjectDialog : public NewProjectDialog
{
  Q_OBJECT

public:
  explicit NewGameProjectDialog(QWidget* parent = nullptr);
  ~NewGameProjectDialog() override;

  [[nodiscard]] std::unique_ptr<Project> create() override;

protected:
  void changeEvent(QEvent* event) override;

private Q_SLOTS:
  void onBrowsePressed();
  void validate();

private:
  void retranslateUi();

private:
  QScopedPointer<Ui::NewGameProjectDialog> m_ui;
};

std::unique_ptr<Project> createProject(Project::Type type);

#endif //NEW_PROJECT_DIALOG_H
