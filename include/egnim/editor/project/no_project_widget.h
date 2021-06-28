#ifndef NO_PROJECT_WIDGET_H
#define NO_PROJECT_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
#include <QSortFilterProxyModel>
/* -------------------------------------------------------------------------- */

namespace Ui { class NoProjectWidget; }
class ProjectListModel;
class ProjectListDelegate;

class NoProjectWidget : public QWidget
{
  Q_OBJECT

public:
  explicit NoProjectWidget(QWidget* parent = nullptr);
  ~NoProjectWidget() override;

protected:
  void changeEvent(QEvent* event) override;

private Q_SLOTS:
  void openProject(const QModelIndex& index);
  void searchProject(const QString& search);

private:
  void retranslateUi();

private:
  QScopedPointer<Ui::NoProjectWidget> m_ui;
  QScopedPointer<ProjectListModel> m_projects_model;
  QScopedPointer<ProjectListDelegate> m_projects_delegate;
  QScopedPointer<QSortFilterProxyModel> m_search_proxy_model;
};

#endif //NO_PROJECT_WIDGET_H
