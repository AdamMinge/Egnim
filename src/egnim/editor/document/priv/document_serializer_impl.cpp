/* ----------------------------------- Local -------------------------------- */
#include "document/priv/document_serializer_impl.h"
#include "document/scene_document.h"
/* ----------------------------------- Engine ------------------------------- */
#include <egnim/engine/core/unique_pointer.h>
/* -------------------------------------------------------------------------- */

namespace priv {

DocumentSerializerImpl::DocumentSerializerImpl() = default;

DocumentSerializerImpl::~DocumentSerializerImpl() = default;

QByteArray DocumentSerializerImpl::serialize(const Document& document) const
{
  if(auto scene_document = dynamic_cast<const SceneDocument*>(std::addressof(document)); scene_document)
    return serializeSceneDocument(*scene_document);

  return QByteArray{};
}

std::unique_ptr<Document> DocumentSerializerImpl::deserialize(const QByteArray& array) const
{
  if(auto scene_document = deserializeSceneDocument(array); scene_document)
    return scene_document;

  return nullptr;
}

} // namespace priv

