/* ----------------------------------- Local -------------------------------- */
#include "document/priv/json_document_serializer_impl.h"
#include <document/scene_document.h>
/* -------------------------------------------------------------------------- */

namespace priv {

JsonDocumentSerializerImpl::JsonDocumentSerializerImpl() = default;

JsonDocumentSerializerImpl::~JsonDocumentSerializerImpl() = default;

QByteArray JsonDocumentSerializerImpl::serializeSceneDocument(const SceneDocument& document) const
{
  // TODO : implementation //
  return QByteArray();
}

std::unique_ptr<SceneDocument> JsonDocumentSerializerImpl::deserializeSceneDocument(const QByteArray& array) const
{
  // TODO : implementation //
  return nullptr;
}

} // namespace priv

