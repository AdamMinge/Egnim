/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/sound_node.h>
#include <egnim/engine/scene/visitor/scene_visitor.h>
#include <egnim/engine/events/sound_event_listener.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene {

SoundNode::SoundNode() :
  m_sound_buffers(nullptr),
  m_default_settings(Settings{}),
  m_listener(std::make_unique<events::SoundEventListener>())
{

}

SoundNode::~SoundNode() = default;

void SoundNode::setSoundBuffers(core::BaseResourceHolder<sf::SoundBuffer, std::string_view>* sound_buffers)
{
  m_sound_buffers = sound_buffers;
}

core::BaseResourceHolder<sf::SoundBuffer, std::string_view>* SoundNode::getSoundBuffers() const
{
  return m_sound_buffers;
}

void SoundNode::setDefaultSettings(const Settings &settings)
{
  m_default_settings = settings;
}

const SoundNode::Settings &SoundNode::getDefaultSettings() const
{
  return m_default_settings;
}

bool SoundNode::play(std::string_view id, sf::Vector2f position)
{
  return playLoop(id, nullptr, m_default_settings, position);
}

bool SoundNode::play(std::string_view id, const Settings &settings, sf::Vector2f position)
{
  return playLoop(id, nullptr, settings, position);
}

bool SoundNode::playLoop(std::string_view id, const std::function<bool()>& stop_condition,
                          sf::Vector2f position)
{
  return playLoop(id, stop_condition, m_default_settings, position);
}

bool SoundNode::playLoop(std::string_view id, const std::function<bool()>& stop_condition,
                          const Settings &settings, sf::Vector2f position)
{
  m_sounds.emplace_back(std::make_pair(sf::Sound{}, stop_condition));
  auto &sound = m_sounds.back().first;

  if (m_sound_buffers && !m_sound_buffers->contains(id))
    return false;

  sound.setBuffer(m_sound_buffers->get(id));
  sound.setPosition(position.x, position.y, 0.f);
  sound.setAttenuation(settings.attenuation);
  sound.setMinDistance(settings.min_distance);
  sound.setPitch(settings.pitch);
  sound.setVolume(settings.volume);
  sound.setLoop(static_cast<bool>(stop_condition));
  sound.play();

  return true;
}

void SoundNode::stopAllSounds()
{
  setAllSounds(sf::Sound::Stopped);
}

void SoundNode::pauseAllSounds()
{
  setAllSounds(sf::Sound::Paused);
}

void SoundNode::startAllSounds()
{
  setAllSounds(sf::Sound::Playing);
}

void SoundNode::accept(SceneVisitor& visitor)
{
  visitor.visitSoundNode(*this);
}

void SoundNode::updateCurrent(sf::Time dt)
{
  checkStopConditions();
  removeStoppedSounds();
}

void SoundNode::checkStopConditions()
{
  std::for_each(m_sounds.begin(), m_sounds.end(), [](auto& sound_pair){
    if(sound_pair.second && sound_pair.second())
      sound_pair.first.stop();
  });
}

void SoundNode::removeStoppedSounds()
{
  m_sounds.remove_if([](const auto& sound){
    return sound.first.getStatus() == sf::Sound::Stopped;
  });
}

void SoundNode::setAllSounds(sf::Sound::Status status)
{
  std::for_each(m_sounds.begin(), m_sounds.end(), [status](auto& sound_pair){
    switch(status)
    {
      case sf::Sound::Stopped:
        sound_pair.first.stop();
        break;

      case sf::Sound::Paused:
        sound_pair.first.pause();
        break;

      case sf::Sound::Playing:
        sound_pair.first.play();
        break;
    }
  });
}

} // namespace egnim::scene
