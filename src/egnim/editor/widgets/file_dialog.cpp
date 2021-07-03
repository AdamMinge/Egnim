/* ------------------------------------ Qt ---------------------------------- */
#include <QToolButton>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QEvent>
#include <QKeyEvent>
#include <QCompleter>
#include <QAbstractItemView>
/* ----------------------------------- Local -------------------------------- */
#include "widgets/file_dialog.h"
/* -------------------------------------------------------------------------- */

FileDialog::FileDialog(const QFileDialogArgs &args) :
  QFileDialog(args)
{
  init();
}

FileDialog::FileDialog(QWidget* parent, Qt::WindowFlags flags) :
  QFileDialog(parent, flags)
{
  init();
}

FileDialog::FileDialog(QWidget* parent, const QString& caption, const QString& directory, const QString& filter) :
  QFileDialog(parent, caption, directory, filter)
{
  init();
}

FileDialog::~FileDialog() = default;

QString FileDialog::getExistingDirectory(QWidget *parent, const QString &caption,
                                         const QString &dir, QFileDialog::Options options, bool fixedTop)
{
  const QStringList schemes = QStringList(QStringLiteral("file"));
  const QUrl selectedUrl = getExistingDirectoryUrl(
    parent, caption, QUrl::fromLocalFile(dir), options, schemes, fixedTop);

  if (selectedUrl.isLocalFile() || selectedUrl.isEmpty())
    return selectedUrl.toLocalFile();
  else
    return selectedUrl.toString();
}

QUrl FileDialog::getExistingDirectoryUrl(QWidget *parent, const QString &caption, const QUrl &dir,
                                         QFileDialog::Options options, const QStringList &supportedSchemes, bool fixedTop)
{
  FileDialog dialog(parent, caption);
  dialog.setDirectoryUrl(dir);
  dialog.setFileMode(FileMode::Directory);
  dialog.setOptions(options);
  dialog.setSupportedSchemes(supportedSchemes);

  if(fixedTop)
    dialog.setTopDir(dir.toLocalFile());

  if (dialog.exec() == QDialog::Accepted)
    return dialog.selectedUrls().value(0);
  return QUrl();
}

void FileDialog::init()
{
  setOptions(QFileDialog::DontUseNativeDialog);

  connect(this, SIGNAL(directoryEntered(QString)), this, SLOT(checkHistory()));
  connect(this, SIGNAL(directoryEntered(QString)), this, SLOT(checkGoToParent()));
  connect(findChild<QToolButton*>("backButton"), SIGNAL(clicked()), this, SLOT(checkGoToParent()));
  connect(findChild<QToolButton*>("forwardButton"), SIGNAL(clicked()), this, SLOT(checkGoToParent()));
  connect(findChild<QLineEdit*>("fileNameEdit"), SIGNAL(textChanged(QString)), this, SLOT(checkLineEdit(QString)));

  findChild<QLineEdit *>("fileNameEdit")->installEventFilter(this);
  findChild<QWidget *>("listView")->installEventFilter(this);
  findChild<QWidget *>("treeView")->installEventFilter(this);
  findChild<QLineEdit *>("fileNameEdit")->completer()->popup()->installEventFilter(this);
}

bool FileDialog::eventFilter(QObject *object, QEvent *event)
{
  if (event->type() != QEvent::KeyPress)
    return false;

  int key = dynamic_cast<QKeyEvent*>(event)->key();
  if(object->objectName() == "listView" || object->objectName() == "treeView")
  {
    return (Qt::Key_Backspace == key && !pathFits(directory().absolutePath()));
  }
  else
  {
    if(Qt::Key_Return != key && Qt::Key_Enter != key)
      return false;

    QString text = findChild<QLineEdit *>("fileNameEdit")->text();
    QString path = QDir::cleanPath(directory().absolutePath() + (text.startsWith("/") ? "" : "/") + text);
    bool a = QDir(text).isAbsolute();

    return !((!a && pathFits(path)) || (a && pathFits(text)));
  }
}

void FileDialog::setTopDir(const QString &path)
{
  if(path == m_top_dir)
    return;

  m_top_dir = (!path.isEmpty() && QFileInfo(path).isDir()) ? path : QString();

  if(!pathFits(path))
  {
    setDirectory(m_top_dir);
    checkHistory();
    checkLineEdit(findChild<QLineEdit*>("fileNameEdit")->text());
  }
  else
  {
    auto line_edit = findChild<QLineEdit*>("fileNameEdit");
    line_edit->setText(line_edit->text());
  }

  findChild<QWidget*>("lookInCombo")->setEnabled(m_top_dir.isEmpty());
  findChild<QWidget*>("sidebar")->setEnabled(m_top_dir.isEmpty());
  checkGoToParent();
}

QString FileDialog::getTopDir() const
{
  return m_top_dir;
}

bool FileDialog::pathFits(const QString &path) const
{
  return m_top_dir.isEmpty() || (path.startsWith(m_top_dir) && path.length() > m_top_dir.length());
}

void FileDialog::checkHistory()
{
  QStringList list = history();
  for (auto i = list.size() - 1; i >= 0; --i)
    if (!pathFits(list.at(i)))
      list.removeAt(i);

  setHistory(list);
}

void FileDialog::checkGoToParent()
{
  findChild<QToolButton*>("toParentButton")->setEnabled(pathFits(directory().absolutePath()));
}

void FileDialog::checkLineEdit(const QString &text)
{
  QAbstractButton *btn = findChild<QDialogButtonBox *>("buttonBox")->buttons().first();
  QString path = QDir::cleanPath(directory().absolutePath() + (text.startsWith("/") ? "" : "/") + text);
  bool a = QDir(text).isAbsolute();
  btn->setEnabled(btn->isEnabled() && ((!a && pathFits(path)) || (a && pathFits(text))));
}
