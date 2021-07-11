#ifndef CONSOLE_DOCK_H
#define CONSOLE_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLineEdit>
#include <QDockWidget>
#include <QPushButton>
#include <QPlainTextEdit>
/* -------------------------------------------------------------------------- */

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

private:
  void retranslateUi();

private:
  QPlainTextEdit* m_plain_text_edit;
  QLineEdit* m_line_edit;
  QPushButton* m_clear_button;
};

#endif //CONSOLE_DOCK_H
