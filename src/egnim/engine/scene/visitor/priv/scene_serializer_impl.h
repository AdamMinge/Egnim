#ifndef SCENE_SERIALIZER_IMPL_H
#define SCENE_SERIALIZER_IMPL_H

namespace egnim::scene
{
  class AnimatedSpriteNode;
  class LabelNode;
  class MusicNode;
  class SceneNode;
  class SoundNode;
  class SpriteNode;
}

namespace egnim::scene::priv
{

  class SceneSerializerImpl
  {
  public:
    virtual ~SceneSerializerImpl() = default;

    virtual void serialize(AnimatedSpriteNode &animated_sprite_node) = 0;
    virtual void deserialize(AnimatedSpriteNode &animated_sprite_node) = 0;

    virtual void serialize(LabelNode &label_node) = 0;
    virtual void deserialize(LabelNode &label_node) = 0;

    virtual void serialize(MusicNode &music_node) = 0;
    virtual void deserialize(MusicNode &music_node) = 0;

    virtual void serialize(SceneNode &scene_node) = 0;
    virtual void deserialize(SceneNode &scene_node) = 0;

    virtual void serialize(SoundNode &sound_node) = 0;
    virtual void deserialize(SoundNode &sound_node) = 0;

    virtual void serialize(SpriteNode &sprite_node) = 0;
    virtual void deserialize(SpriteNode &sprite_node) = 0;

  protected:
    explicit SceneSerializerImpl() = default;
  };

} // egnim::scene::priv

#endif //SCENE_SERIALIZER_IMPL_H
