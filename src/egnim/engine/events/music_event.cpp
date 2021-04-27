/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/music_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events
{

/* ------------------------------- SoundPlayEvent --------------------------- */

MusicPlayEvent::MusicPlayEvent(std::string_view music_id, bool loop, std::optional<scene::MusicNode::Settings> music_settings) :
  Event(Type::Music),
  m_music_id(music_id),
  m_music_settings(music_settings),
  m_music_loop(loop)
{

}

MusicPlayEvent::~MusicPlayEvent() = default;

void MusicPlayEvent::setMusicId(std::string_view music_id)
{
  m_music_id = music_id;
}

std::string_view MusicPlayEvent::getMusicId() const
{
  return m_music_id;
}

void MusicPlayEvent::setMusicSettings(const scene::MusicNode::Settings &music_settings)
{
  m_music_settings = music_settings;
}

const scene::MusicNode::Settings& MusicPlayEvent::getMusicSettings() const
{
  assert(hasMusicSettings());
  return m_music_settings.value();
}

void MusicPlayEvent::setAsLoop(bool loop)
{
  m_music_loop = loop;
}

bool MusicPlayEvent::hasMusicSettings() const
{
  return m_music_settings.has_value();
}

bool MusicPlayEvent::isLoopMusic() const
{
  return m_music_loop;
}

/* ----------------------------- SoundControlEvent -------------------------- */

MusicControlEvent::MusicControlEvent(sf::Music::Status music_status) :
  Event(Type::Music),
  m_music_status(music_status)
{

}

MusicControlEvent::~MusicControlEvent() = default;

void MusicControlEvent::setStatus(sf::Music::Status music_status)
{
  m_music_status = music_status;
}

sf::Music::Status MusicControlEvent::getStatus() const
{
  return m_music_status;
}

} // namespace egnim::events