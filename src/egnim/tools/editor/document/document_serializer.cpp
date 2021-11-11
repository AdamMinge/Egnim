/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/document/document_serializer.h"
#include "egnim/tools/editor/document/document.h"
#include "egnim/tools/editor/document/priv/json_document_serializer_impl.h"
/* -------------------------------------------------------------------------- */

DocumentSerializer::DocumentSerializer() = default;
DocumentSerializer::~DocumentSerializer() = default;

QByteArray DocumentSerializer::serialize(const Document& document, Format format) const
{
  auto impl = getImpl(format);
  Q_ASSERT(impl);

  return impl->serialize(document);
}

std::unique_ptr<Document> DocumentSerializer::deserialize(const QByteArray& array, Format format) const
{
  auto impl = getImpl(format);
  Q_ASSERT(impl);

  return impl->deserialize(array);
}

std::unique_ptr<priv::DocumentSerializerImpl> DocumentSerializer::getImpl(Format format) const
{
  switch(format)
  {
    case Format::Json:
      return std::make_unique<priv::JsonDocumentSerializerImpl>();
  }

  return nullptr;
}