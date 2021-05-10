/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/music_node.h>
#include <egnim/engine/scene/scene_visitor.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene {

MusicNode::MusicNode() :
  m_musics_holder(nullptr),
  m_default_settings(Settings{}),
  m_current_music(nullptr)
{

}

MusicNode::~MusicNode() = default;

void MusicNode::setMusicsHolder(core::BaseResourceHolder<sf::Music, std::string_view>* musics_holder)
{
  m_musics_holder = musics_holder;
}

core::BaseResourceHolder<sf::Music, std::string_view>* MusicNode::getMusicsHolder() const
{
  return m_musics_holder;
}

void MusicNode::setDefaultSettings(const Settings& settings)
{
  m_default_settings = settings;
}

const MusicNode::Settings& MusicNode::getDefaultSettings() const
{
  return m_default_settings;
}

bool MusicNode::play()
{
  if(!m_current_music)
    return false;

  m_current_music->play();
  return true;
}

bool MusicNode::play(std::string_view id, bool loop)
{
  return play(id, m_default_settings, loop);
}

bool MusicNode::play(std::string_view id, const Settings& settings, bool loop)
{
  if (m_musics_holder && !m_musics_holder->contains(id))
    return false;

  m_current_music = &m_musics_holder->get(id);

  m_current_music->setAttenuation(settings.attenuation);
  m_current_music->setMinDistance(settings.min_distance);
  m_current_music->setPitch(settings.pitch);
  m_current_music->setVolume(settings.volume);
  m_current_music->setLoop(loop);
  m_current_music->play();

  return true;
}

void MusicNode::stop()
{
  if(m_current_music)
    m_current_music->stop();
}

void MusicNode::pause()
{
  if(m_current_music)
    m_current_music->pause();
}

bool MusicNode::isPlaying()
{
  return m_current_music && m_current_music->getStatus() == sf::Music::Playing;
}

bool MusicNode::isPaused()
{
  return m_current_music && m_current_music->getStatus() == sf::Music::Paused;
}

bool MusicNode::isStopped()
{
  return m_current_music && m_current_music->getStatus() == sf::Music::Stopped;
}

void MusicNode::accept(SceneVisitor& visitor)
{
  visitor.visitMusicNode(*this);
}

std::unique_ptr<Node> MusicNode::clone() const
{
  auto clone_node = std::make_unique<MusicNode>();
  Node::initializeClone(*clone_node);

  clone_node->m_musics_holder = m_musics_holder;
  clone_node->m_default_settings = m_default_settings;
  clone_node->m_current_music = nullptr;

  return clone_node;
}

} // namespace egnim::scene