#ifndef JSON_SCENE_SERIALIZER_IMPL_H
#define JSON_SCENE_SERIALIZER_IMPL_H

/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/priv/scene_serializer_impl.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{
  class Node;
}

namespace egnim::scene::priv
{

  class JsonSceneSerializerImpl : public SceneSerializerImpl
  {
  public:
    explicit JsonSceneSerializerImpl();
    ~JsonSceneSerializerImpl() override;

    void serialize(const AnimatedSpriteNode &animated_sprite_node, std::ostream& stream) override;
    void deserialize(AnimatedSpriteNode &animated_sprite_node, std::istream& stream) override;

    void serialize(const LabelNode &label_node, std::ostream& stream) override;
    void deserialize(LabelNode &label_node, std::istream& stream) override;

    void serialize(const MusicNode &music_node, std::ostream& stream) override;
    void deserialize(MusicNode &music_node, std::istream& stream) override;

    void serialize(const SceneNode &scene_node, std::ostream& stream) override;
    void deserialize(SceneNode &scene_node, std::istream& stream) override;

    void serialize(const SoundNode &sound_node, std::ostream& stream) override;
    void deserialize(SoundNode &sound_node, std::istream& stream) override;

    void serialize(const SpriteNode &sprite_node, std::ostream& stream) override;
    void deserialize(SpriteNode &sprite_node, std::istream& stream) override;

    void serialize(const CameraNode &camera_node, std::ostream& stream) override;
    void deserialize(CameraNode &camera_node, std::istream& stream) override;

    void serialize(const TileMapNode &tile_map_node, std::ostream& stream) override;
    void deserialize(TileMapNode &tile_map_node, std::istream& stream) override;

    void serialize(const physics::PhysicsBody &physics_body, std::ostream& stream) override;
    void deserialize(physics::PhysicsBody &physics_body, std::istream& stream) override;

    void serialize(const physics::PhysicsJoint &physics_joint, std::ostream& stream) override;
    void deserialize(physics::PhysicsJoint &physics_joint, std::istream& stream) override;

  private:
    void serialize(const Node &node, std::ostream& stream);
    void deserialize(Node &node, std::istream& stream);
  };

} // namespace egnim::scene::priv

#endif //JSON_SCENE_SERIALIZER_IMPL_H
