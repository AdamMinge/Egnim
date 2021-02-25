#ifndef SCENE_SERIALIZER_IMPL_H
#define SCENE_SERIALIZER_IMPL_H

/* --------------------------------- Standard ------------------------------- */
#include <ios>
/* -------------------------------------------------------------------------- */

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

    virtual void serialize(const AnimatedSpriteNode &animated_sprite_node, std::ostream& stream) = 0;
    virtual void deserialize(AnimatedSpriteNode &animated_sprite_node, std::istream& stream) = 0;

    virtual void serialize(const LabelNode &label_node, std::ostream& stream) = 0;
    virtual void deserialize(LabelNode &label_node, std::istream& stream) = 0;

    virtual void serialize(const MusicNode &music_node, std::ostream& stream) = 0;
    virtual void deserialize(MusicNode &music_node, std::istream& stream) = 0;

    virtual void serialize(const SceneNode &scene_node, std::ostream& stream) = 0;
    virtual void deserialize(SceneNode &scene_node, std::istream& stream) = 0;

    virtual void serialize(const SoundNode &sound_node, std::ostream& stream) = 0;
    virtual void deserialize(SoundNode &sound_node, std::istream& stream) = 0;

    virtual void serialize(const SpriteNode &sprite_node, std::ostream& stream) = 0;
    virtual void deserialize(SpriteNode &sprite_node, std::istream& stream) = 0;

  protected:
    explicit SceneSerializerImpl() = default;
  };

} // egnim::scene::priv

#endif //SCENE_SERIALIZER_IMPL_H
