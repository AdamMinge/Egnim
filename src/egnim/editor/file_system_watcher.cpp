/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
/* ----------------------------------- Local -------------------------------- */
#include "file_system_watcher.h"
/* -------------------------------------------------------------------------- */

FileSystemWatcher::FileSystemWatcher(QObject* parent) :
  QObject(parent)
{
  m_changed_paths_timer.setInterval(500);
  m_changed_paths_timer.setSingleShot(true);

  connect(std::addressof(m_watcher), &QFileSystemWatcher::fileChanged,
          this, &FileSystemWatcher::onFileChanged);
  connect(std::addressof(m_watcher), &QFileSystemWatcher::directoryChanged,
          this, &FileSystemWatcher::onDirectoryChanged);

  connect(std::addressof(m_changed_paths_timer), &QTimer::timeout,
          this, &FileSystemWatcher::pathsChangedTimeout);
}

FileSystemWatcher::~FileSystemWatcher() = default;

void FileSystemWatcher::addPath(const QString& path)
{
  if(QFile::exists(path))
    m_watcher.addPath(path);
}

void FileSystemWatcher::addPaths(const QStringList& paths)
{
  for(auto& path : paths)
    addPath(path);
}

void FileSystemWatcher::removePath(const QString& path)
{
  m_watcher.removePath(path);
}

void FileSystemWatcher::removePaths(const QStringList& paths)
{
  for(auto& path : paths)
    removePath(path);
}

QStringList FileSystemWatcher::getPaths() const
{
  return getFilePaths() << getDirectoryPaths();
}

QStringList FileSystemWatcher::getFilePaths() const
{
  return m_watcher.files();
}

QStringList FileSystemWatcher::getDirectoryPaths() const
{
  return m_watcher.directories();
}

void FileSystemWatcher::clear()
{
  m_watcher.removePaths(getPaths());
}

void FileSystemWatcher::onFileChanged(const QString& path)
{
  m_changed_paths.insert(path);
  m_changed_paths_timer.start();

  Q_EMIT fileChanged(path);
}

void FileSystemWatcher::onDirectoryChanged(const QString& path)
{
  m_changed_paths.insert(path);
  m_changed_paths_timer.start();

  Q_EMIT directoryChanged(path);
}

void FileSystemWatcher::pathsChangedTimeout()
{
  const auto changed_paths = m_changed_paths.values();
  for(const auto& path : changed_paths)
  {
    if(getFilePaths().contains(path) && QFile::exists(path))
      m_watcher.addPath(path);
  }

  Q_EMIT pathsChanged(changed_paths);
  m_changed_paths.clear();
}
