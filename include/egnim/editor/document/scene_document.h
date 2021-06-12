#ifndef SCENE_DOCUMENT_H
#define SCENE_DOCUMENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDateTime>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/document/document.h>
/* -------------------------------------------------------------------------- */

class SceneDocument : public Document
{
  Q_OBJECT

public:
  static std::unique_ptr<SceneDocument> create(const QString& file_name);

public:
  ~SceneDocument() override;

  [[nodiscard]] const QDateTime& getLastModified() const;

protected:
  explicit SceneDocument(QString file_name, QObject* parent = nullptr);

private:
  QDateTime m_last_modified;
};

#endif //SCENE_DOCUMENT_H
