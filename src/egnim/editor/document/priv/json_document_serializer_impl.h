#ifndef JSON_PROJECT_SERIALIZER_IMPL_H
#define JSON_PROJECT_SERIALIZER_IMPL_H

/* ------------------------------------ Local ---------------------------------- */
#include "document/priv/document_serializer_impl.h"
/* -------------------------------------------------------------------------- */

namespace priv
{

  class JsonDocumentSerializerImpl : public DocumentSerializerImpl
  {
  public:
    JsonDocumentSerializerImpl();
    ~JsonDocumentSerializerImpl() override;

  protected:
    [[nodiscard]] QByteArray serializeSceneDocument(const SceneDocument& document) const override;
    [[nodiscard]] std::unique_ptr<SceneDocument> deserializeSceneDocument(const QByteArray& array) const override;
  };

} // namespace priv

#endif //JSON_PROJECT_SERIALIZER_IMPL_H
