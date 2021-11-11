#ifndef PROJECT_SERIALIZER_H
#define PROJECT_SERIALIZER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QByteArray>
/* -------------------------------------------------------------------------- */

class Document;

namespace priv
{
  class DocumentSerializerImpl;
}

class DocumentSerializer
{
public:
  enum class Format
  {
    Json,
  };

public:
  DocumentSerializer();
  ~DocumentSerializer();

  [[nodiscard]] QByteArray serialize(const Document& project, Format format = Format::Json) const;
  [[nodiscard]] std::unique_ptr<Document> deserialize(const QByteArray& array, Format format = Format::Json) const;

private:
  [[nodiscard]] std::unique_ptr<priv::DocumentSerializerImpl> getImpl(Format format) const;
};

#endif //PROJECT_SERIALIZER_H
