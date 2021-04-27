/* --------------------------------- Standard ------------------------------- */
#include <cassert>
#include <utility>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/sound_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events {

/* ------------------------------- SoundPlayEvent --------------------------- */

SoundPlayEvent::SoundPlayEvent(std::string_view sound_id, const sf::Vector2f& sound_position,
                               std::optional<scene::SoundNode::Settings> sound_settings) :
  SoundPlayEvent(sound_id, nullptr, sound_position, sound_settings)
{
  m_sound_loop = false;
}

SoundPlayEvent::SoundPlayEvent(std::string_view sound_id, std::function<bool()> sound_stop_condition,
                               const sf::Vector2f& sound_position, std::optional<scene::SoundNode::Settings> sound_settings) :
  Event(Type::Sound),
  m_sound_id(sound_id),
  m_sound_position(sound_position),
  m_sound_settings(sound_settings),
  m_sound_stop_condition(std::move(sound_stop_condition)),
  m_sound_loop(true)
{

}

SoundPlayEvent::~SoundPlayEvent() = default;

void SoundPlayEvent::setSoundId(std::string_view sound_id)
{
  m_sound_id = sound_id;
}

std::string_view SoundPlayEvent::getSoundId() const
{
  return m_sound_id;
}

void SoundPlayEvent::setSoundPosition(const sf::Vector2f& sound_position)
{
  m_sound_position = sound_position;
}

const sf::Vector2f& SoundPlayEvent::getSoundPosition() const
{
  return m_sound_position;
}

void SoundPlayEvent::setSoundSettings(const scene::SoundNode::Settings& sound_settings)
{
  m_sound_settings = sound_settings;
}

const scene::SoundNode::Settings& SoundPlayEvent::getSoundSettings() const
{
  assert(hasSoundSettings());
  return m_sound_settings.value();
}

void SoundPlayEvent::setAsLoop(bool loop)
{
  m_sound_loop = loop;
}

void SoundPlayEvent::setStopCondition(std::function<bool()> sound_stop_condition)
{
  m_sound_stop_condition = std::move(sound_stop_condition);
}

const std::function<bool()>& SoundPlayEvent::getSoundStopCondition()
{
  return m_sound_stop_condition;
}

bool SoundPlayEvent::hasSoundSettings() const
{
  return m_sound_settings.has_value();
}

bool SoundPlayEvent::isLoopSound() const
{
  return m_sound_loop;
}

/* ----------------------------- SoundControlEvent -------------------------- */

SoundControlEvent::SoundControlEvent(sf::Sound::Status sound_status) :
  Event(Type::Sound),
  m_sound_status(sound_status)
{

}

SoundControlEvent::~SoundControlEvent() = default;

void SoundControlEvent::setStatus(sf::Sound::Status sound_status)
{
  m_sound_status = sound_status;
}

sf::Sound::Status SoundControlEvent::getStatus() const
{
  return m_sound_status;
}

} // namespace egnim::events