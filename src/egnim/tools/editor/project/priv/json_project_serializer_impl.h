#ifndef JSON_PROJECT_SERIALIZER_IMPL_H
#define JSON_PROJECT_SERIALIZER_IMPL_H

/* ------------------------------------ Local ---------------------------------- */
#include "egnim/tools/editor/project/priv/project_serializer_impl.h"
/* -------------------------------------------------------------------------- */

namespace priv
{

  class JsonProjectSerializerImpl : public ProjectSerializerImpl
  {
  public:
    JsonProjectSerializerImpl();
    ~JsonProjectSerializerImpl() override;

  protected:
    [[nodiscard]] QByteArray serializeGameProject(const GameProject& project) const override;
    [[nodiscard]] std::unique_ptr<GameProject> deserializeGameProject(const QByteArray& array) const override;
  };

} // namespace priv

#endif //JSON_PROJECT_SERIALIZER_IMPL_H
