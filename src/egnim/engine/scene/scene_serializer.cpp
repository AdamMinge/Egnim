/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/scene_serializer.h>
/* ------------------------------- Private Local ---------------------------- */
#include <egnim/engine/scene/priv/json_scene_serializer_impl.h>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* -------------------------------------------------------------------------- */


namespace egnim::scene {

SceneSerializer::SceneSerializer(Format format, std::ostream& stream) :
  m_format(format),
  m_action(Action::Serialize),
  m_stream(stream),
  m_impl(nullptr)
{

}

SceneSerializer::SceneSerializer(Format format, std::istream& stream) :
  m_format(format),
  m_action(Action::Deserialize),
  m_stream(stream),
  m_impl(nullptr)
{

}

SceneSerializer::~SceneSerializer() = default;

void SceneSerializer::visitAnimatedSpriteNode(AnimatedSpriteNode& animated_sprite_node)
{
  visit(animated_sprite_node, getImpl());
}

void SceneSerializer::visitLabelNode(LabelNode& label_node)
{
  visit(label_node, getImpl());
}

void SceneSerializer::visitMusicNode(MusicNode& music_node)
{
  visit(music_node, getImpl());
}

void SceneSerializer::visitSceneNode(SceneNode& scene_node)
{
  visit(scene_node, getImpl());
}

void SceneSerializer::visitSoundNode(SoundNode& sound_node)
{
  visit(sound_node, getImpl());
}

void SceneSerializer::visitSpriteNode(SpriteNode& sprite_node)
{
  visit(sprite_node, getImpl());
}

void SceneSerializer::visitCameraNode(CameraNode& camera_node)
{
  visit(camera_node, getImpl());
}

void SceneSerializer::visitTileMapNode(TileMapNode& tile_map_node)
{
  visit(tile_map_node, getImpl());
}

void SceneSerializer::visitPhysicsBody(physics::PhysicsBody& physics_body)
{
  visit(physics_body, getImpl());
}

void SceneSerializer::visitPhysicsJoint(physics::PhysicsJoint& physics_joint)
{
  visit(physics_joint, getImpl());
}

SceneSerializer::Format SceneSerializer::getFormat()
{
  return m_format;
}

SceneSerializer::Action SceneSerializer::getAction()
{
  return m_action;
}

priv::SceneSerializerImpl& SceneSerializer::getImpl()
{
  if(!m_impl)
  {
    switch(getFormat())
    {
      case Format::Json:
        m_impl = std::make_unique<priv::JsonSceneSerializerImpl>();
        break;
    }
  }

  assert(m_impl);
  return *m_impl;
}

} // namespace egnim::scene