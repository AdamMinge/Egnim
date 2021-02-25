#ifndef JSON_SCENE_SERIALIZER_IMPL_H
#define JSON_SCENE_SERIALIZER_IMPL_H

/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/visitor/priv/scene_serializer_impl.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene::priv
{

  class JsonSceneSerializerImpl : public SceneSerializerImpl
  {
  public:
    explicit JsonSceneSerializerImpl();
    ~JsonSceneSerializerImpl() override;

    void serialize(AnimatedSpriteNode &animated_sprite_node) override;
    void deserialize(AnimatedSpriteNode &animated_sprite_node) override;

    void serialize(LabelNode &label_node) override;
    void deserialize(LabelNode &label_node) override;

    void serialize(MusicNode &music_node) override;
    void deserialize(MusicNode &music_node) override;

    void serialize(SceneNode &scene_node) override;
    void deserialize(SceneNode &scene_node) override;

    void serialize(SoundNode &sound_node) override;
    void deserialize(SoundNode &sound_node) override;

    void serialize(SpriteNode &sprite_node) override;
    void deserialize(SpriteNode &sprite_node) override;
  };

} // namespace egnim::scene::priv

#endif //JSON_SCENE_SERIALIZER_IMPL_H
