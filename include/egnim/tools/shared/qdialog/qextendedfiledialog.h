#ifndef EGNIM_TOOLS_EXTENDED_FILE_DIALOG_H
#define EGNIM_TOOLS_EXTENDED_FILE_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QFileDialog>
/* -------------------------------- Tools Shared ---------------------------- */
#include <egnim/tools/shared/export.h>
/* -------------------------------------------------------------------------- */

namespace tools
{

  class TOOLS_SHARED_API QExtendedFileDialog : public QFileDialog
  {
    Q_OBJECT

  public:
    explicit QExtendedFileDialog(QWidget* parent, Qt::WindowFlags flags);
    explicit QExtendedFileDialog(QWidget* parent = nullptr, const QString& caption = QString(),
               const QString& directory = QString(), const QString& filter = QString());
    ~QExtendedFileDialog() override;

    static QString getExistingDirectory(
        QWidget *parent = nullptr, const QString &caption = QString(),
        const QString &dir = QString(), QFileDialog::Options options = ShowDirsOnly,
        const QString& top_dir = QString());

    static QUrl getExistingDirectoryUrl(
        QWidget *parent = nullptr, const QString &caption = QString(),
        const QUrl &dir = QUrl(), QFileDialog::Options options = ShowDirsOnly,
        const QStringList &supportedSchemes = QStringList(),
        const QString& top_dir = QString());

    void setTopDir(const QString &path);
    [[nodiscard]] QString getTopDir() const;

  public:
    bool eventFilter(QObject *object, QEvent *event) override;

  protected:
    explicit QExtendedFileDialog(const QFileDialogArgs &args);
    void init();

  private:
    [[nodiscard]] bool pathFits(const QString &path, bool exact = false) const;

  private Q_SLOTS:
    void checkHistory();
    void checkGoToParentAndBack();
    void checkLineEdit(const QString &text);
    void checkComboBox(int index);

  private:
    QString m_top_dir;
  };

} // namespace tools

#endif //EGNIM_TOOLS_EXTENDED_FILE_DIALOG_H
