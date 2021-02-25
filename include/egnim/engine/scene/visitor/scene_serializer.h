#ifndef SCENE_SERIALIZER_H
#define SCENE_SERIALIZER_H

/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <map>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/visitor/scene_visitor.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene::priv
{
  class SceneSerializerImpl;
}

namespace egnim::scene
{

  class SceneSerializer : public SceneVisitor
  {
  public:
    enum class Action;
    enum class Format;

  public:
    explicit SceneSerializer(Action action, Format format);
    ~SceneSerializer();

    void visit(AnimatedSpriteNode& animated_sprite_node) override;
    void visit(LabelNode& label_node) override;
    void visit(MusicNode& music_node) override;
    void visit(SceneNode& scene_node) override;
    void visit(SoundNode& sound_node) override;
    void visit(SpriteNode& sprite_node) override;

    Action getAction();
    void setAction(Action action);

    Format getFormat();
    void setFormat(Format format);

  protected:
    priv::SceneSerializerImpl& getImpl();

  private:
    Action m_action;
    Format m_format;

    std::unique_ptr<priv::SceneSerializerImpl> m_impl;
  };

  enum class SceneSerializer::Action
  {
    Serialize,
    Deserialize,
  };

  enum class SceneSerializer::Format
  {
    Json,
  };

} // namespace egnim::scene

#endif //SCENE_SERIALIZER_H
