#ifndef PROJECT_DOCK_H
#define PROJECT_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QFileSystemModel>
/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/document/document.h"
/* -------------------------------------------------------------------------- */

namespace Ui { class ProjectDock; }
class Project;
class ProjectFileSystemProxyModel;

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

  void newDocument(Document::Type type);
  void newDirectory();

protected:
  void changeEvent(QEvent* event) override;
  void onContextMenu(const QPoint& pos);

private Q_SLOTS:
  void searchProjectFiles(const QString& search);
  void openProjectFile(const QModelIndex& index);

  void open(const QModelIndex& index);
  void remove(const QModelIndex& index);
  void rename(const QModelIndex& index);

private:
  void retranslateUi();

  [[nodiscard]] QString getCurrentDirectory() const;

private:
  QScopedPointer<Ui::ProjectDock> m_ui;
  QScopedPointer<QFileSystemModel> m_files_model;
  QScopedPointer<ProjectFileSystemProxyModel> m_proxy_model;

  Project* m_current_project;
};

#endif //PROJECT_DOCK_H
