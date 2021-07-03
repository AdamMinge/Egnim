#ifndef FILE_DIALOG_H
#define FILE_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QFileDialog>
/* -------------------------------------------------------------------------- */

class FileDialog : public QFileDialog
{
  Q_OBJECT

public:
  explicit FileDialog(QWidget* parent, Qt::WindowFlags flags);
  explicit FileDialog(QWidget* parent = nullptr, const QString& caption = QString(),
             const QString& directory = QString(), const QString& filter = QString());
  ~FileDialog() override;

  static QString getExistingDirectory(QWidget *parent = nullptr, const QString &caption = QString(),
                                      const QString &dir = QString(), QFileDialog::Options options = ShowDirsOnly,
                                      bool fixedTop = false);

  static QUrl getExistingDirectoryUrl(QWidget *parent = nullptr, const QString &caption = QString(),
                                      const QUrl &dir = QUrl(), QFileDialog::Options options = ShowDirsOnly,
                                      const QStringList &supportedSchemes = QStringList(),
                                      bool fixedTop = false);

  void setTopDir(const QString &path);
  [[nodiscard]] QString getTopDir() const;

public:
  bool eventFilter(QObject *object, QEvent *event) override;

protected:
  explicit FileDialog(const QFileDialogArgs &args);
  void init();

private:
  [[nodiscard]] bool pathFits(const QString &path) const;

private Q_SLOTS:
  void checkHistory();
  void checkGoToParent();
  void checkLineEdit(const QString &text);

private:
  QString m_top_dir;
};

#endif //FILE_DIALOG_H
