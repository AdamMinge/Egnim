/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/priv/json_scene_serializer_impl.h>
#include <egnim/engine/scene/node.h>
#include <egnim/engine/scene/label_node.h>
#include <egnim/engine/scene/sound_node.h>
#include <egnim/engine/scene/music_node.h>
#include <egnim/engine/scene/sprite_node.h>
#include <egnim/engine/scene/scene_node.h>
#include <egnim/engine/scene/animated_sprite_node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene::priv {

JsonSceneSerializerImpl::JsonSceneSerializerImpl() = default;

JsonSceneSerializerImpl::~JsonSceneSerializerImpl() = default;

void JsonSceneSerializerImpl::serialize(const AnimatedSpriteNode &animated_sprite_node, std::ostream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::deserialize(AnimatedSpriteNode &animated_sprite_node, std::istream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::serialize(const LabelNode &label_node, std::ostream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::deserialize(LabelNode &label_node, std::istream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::serialize(const MusicNode &music_node, std::ostream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::deserialize(MusicNode &music_node, std::istream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::serialize(const SceneNode &scene_node, std::ostream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::deserialize(SceneNode &scene_node, std::istream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::serialize(const SoundNode &sound_node, std::ostream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::deserialize(SoundNode &sound_node, std::istream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::serialize(const SpriteNode &sprite_node, std::ostream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::deserialize(SpriteNode &sprite_node, std::istream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::serialize(const CameraNode &camera_node, std::ostream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::deserialize(CameraNode &camera_node, std::istream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::serialize(const Node &node, std::ostream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::deserialize(Node &node, std::istream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::serialize(const TileMapNode &tile_map_node, std::ostream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::deserialize(TileMapNode &tile_map_node, std::istream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::serialize(const physics::PhysicsBody &physics_body, std::ostream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::deserialize(physics::PhysicsBody &physics_body, std::istream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::serialize(const physics::PhysicsJoint &physics_joint, std::ostream& stream)
{
  // TODO : implementation //
}

void JsonSceneSerializerImpl::deserialize(physics::PhysicsJoint &physics_joint, std::istream& stream)
{
  // TODO : implementation //
}

} // namespace egnim::scene::priv