/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/visitor/scene_serializer.h>
/* ------------------------------- Private Local ---------------------------- */
#include <egnim/engine/scene/visitor/priv/json_scene_serializer_impl.h>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* -------------------------------------------------------------------------- */


namespace egnim::scene {

SceneSerializer::SceneSerializer(Action action, Format format) :
  m_action(action),
  m_format(format),
  m_impl(nullptr)
{

}

SceneSerializer::~SceneSerializer() = default;

void SceneSerializer::visit(AnimatedSpriteNode& animated_sprite_node)
{
  if(getAction() == Action::Serialize)
    getImpl().serialize(animated_sprite_node);
  else if(getAction() == Action::Deserialize)
    getImpl().deserialize(animated_sprite_node);
}

void SceneSerializer::visit(LabelNode& label_node)
{
  if(getAction() == Action::Serialize)
    getImpl().serialize(label_node);
  else if(getAction() == Action::Deserialize)
    getImpl().deserialize(label_node);
}

void SceneSerializer::visit(MusicNode& music_node)
{
  if(getAction() == Action::Serialize)
    getImpl().serialize(music_node);
  else if(getAction() == Action::Deserialize)
    getImpl().deserialize(music_node);
}

void SceneSerializer::visit(SceneNode& scene_node)
{
  if(getAction() == Action::Serialize)
    getImpl().serialize(scene_node);
  else if(getAction() == Action::Deserialize)
    getImpl().deserialize(scene_node);
}

void SceneSerializer::visit(SoundNode& sound_node)
{
  if(getAction() == Action::Serialize)
    getImpl().serialize(sound_node);
  else if(getAction() == Action::Deserialize)
    getImpl().deserialize(sound_node);
}

void SceneSerializer::visit(SpriteNode& sprite_node)
{
  if(getAction() == Action::Serialize)
    getImpl().serialize(sprite_node);
  else if(getAction() == Action::Deserialize)
    getImpl().deserialize(sprite_node);
}

SceneSerializer::Action SceneSerializer::getAction()
{
  return m_action;
}

void SceneSerializer::setAction(Action action)
{
  m_action = action;
}

SceneSerializer::Format SceneSerializer::getFormat()
{
  return m_format;
}

void SceneSerializer::setFormat(Format format)
{
  m_format = format;
  m_impl.reset(nullptr);
}

priv::SceneSerializerImpl& SceneSerializer::getImpl()
{
  if(!m_impl)
  {
    switch(getFormat())
    {
      case Format::Json:
        m_impl = std::make_unique<priv::JsonSceneSerializerImpl>();
    }
  }

  assert(m_impl);
  return *m_impl;
}

} // namespace egnim::scene