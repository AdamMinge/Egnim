#ifndef PROJECT_DOCK_H
#define PROJECT_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QFileSystemModel>
/* -------------------------------------------------------------------------- */

namespace Ui { class ProjectDock; }
class Project;
class FileSystemProxyModel;

class ProjectDock final : public QDockWidget
{
  Q_OBJECT

private:
  enum Column
  {
    Column_Name,
    Column_Size,
    Column_Type,
    Column_Date_Modified
  };

public:
  explicit ProjectDock(QWidget* parent = nullptr);
  ~ProjectDock() override;

  void setCurrentProject(Project* project);
  [[nodiscard]] Project* getCurrentProject() const;

protected:
  void changeEvent(QEvent* event) override;

private Q_SLOTS:
  void searchProjectFiles(const QString& search);
  void onDoubleClicked(const QModelIndex& index);

private:
  void retranslateUi();

private:
  QScopedPointer<Ui::ProjectDock> m_ui;
  QScopedPointer<QFileSystemModel> m_files_model;
  QScopedPointer<FileSystemProxyModel> m_proxy_model;

  Project* m_current_project;
};

#endif //PROJECT_DOCK_H
