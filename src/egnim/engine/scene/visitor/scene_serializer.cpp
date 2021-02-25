/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/visitor/scene_serializer.h>
/* ------------------------------- Private Local ---------------------------- */
#include <egnim/engine/scene/visitor/priv/json_scene_serializer_impl.h>
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

void SceneSerializer::visit(AnimatedSpriteNode& animated_sprite_node)
{
  if(getAction() == Action::Serialize)
    getImpl().serialize(animated_sprite_node, std::get<ostream>(m_stream));
  else if(getAction() == Action::Deserialize)
    getImpl().deserialize(animated_sprite_node, std::get<istream>(m_stream));
}

void SceneSerializer::visit(LabelNode& label_node)
{
  if(getAction() == Action::Serialize)
    getImpl().serialize(label_node, std::get<ostream>(m_stream));
  else if(getAction() == Action::Deserialize)
    getImpl().deserialize(label_node, std::get<istream>(m_stream));
}

void SceneSerializer::visit(MusicNode& music_node)
{
  if(getAction() == Action::Serialize)
    getImpl().serialize(music_node, std::get<ostream>(m_stream));
  else if(getAction() == Action::Deserialize)
    getImpl().deserialize(music_node, std::get<istream>(m_stream));
}

void SceneSerializer::visit(SceneNode& scene_node)
{
  if(getAction() == Action::Serialize)
    getImpl().serialize(scene_node, std::get<ostream>(m_stream));
  else if(getAction() == Action::Deserialize)
    getImpl().deserialize(scene_node, std::get<istream>(m_stream));
}

void SceneSerializer::visit(SoundNode& sound_node)
{
  if(getAction() == Action::Serialize)
    getImpl().serialize(sound_node, std::get<ostream>(m_stream));
  else if(getAction() == Action::Deserialize)
    getImpl().deserialize(sound_node, std::get<istream>(m_stream));
}

void SceneSerializer::visit(SpriteNode& sprite_node)
{
  if(getAction() == Action::Serialize)
    getImpl().serialize(sprite_node, std::get<ostream>(m_stream));
  else if(getAction() == Action::Deserialize)
    getImpl().deserialize(sprite_node, std::get<istream>(m_stream));
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