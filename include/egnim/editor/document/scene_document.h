#ifndef SCENE_DOCUMENT_H
#define SCENE_DOCUMENT_H

/* ----------------------------------- Local -------------------------------- */
#include "document/document.h"
/* -------------------------------------------------------------------------- */

class SceneDocument : public Document
{
  Q_OBJECT

public:
  static std::unique_ptr<SceneDocument> create();

public:
  ~SceneDocument() override;

protected:
  explicit SceneDocument(QObject* parent = nullptr);

};

#endif //SCENE_DOCUMENT_H
