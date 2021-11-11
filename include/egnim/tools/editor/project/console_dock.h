#ifndef CONSOLE_DOCK_H
#define CONSOLE_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLineEdit>
#include <QDockWidget>
#include <QPushButton>
#include <QPlainTextEdit>
/* -------------------------------------------------------------------------- */

class Issue;
class QLineEditWithHistory;

class ConsoleOutputWidget : public QPlainTextEdit
{
  Q_OBJECT

public:
  using QPlainTextEdit::QPlainTextEdit;

protected:
  void contextMenuEvent(QContextMenuEvent *event) override;
};

class ConsoleDock final : public QDockWidget
{
  Q_OBJECT

public:
  explicit ConsoleDock(QWidget* parent = nullptr);
  ~ConsoleDock() override;

protected:
  void changeEvent(QEvent* event) override;

private Q_SLOTS:
  void onInfoIssueReport(const Issue& issue);
  void onWarningIssueReport(const Issue& issue);
  void onErrorIssueReport(const Issue& issue);

  void executeScript();

private:
  void retranslateUi();

private:
  QPlainTextEdit* m_plain_text_edit;
  QLineEditWithHistory* m_line_edit_with_history;
  QPushButton* m_clear_button;
};

#endif //CONSOLE_DOCK_H
