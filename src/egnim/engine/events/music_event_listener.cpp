/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/music_event_listener.h>
#include <egnim/engine/events/music_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events {

MusicEventListener::MusicEventListener() :
  EventListener(static_cast<int32_t>(Event::Type::Music))
{

}

MusicEventListener::~MusicEventListener() = default;

void MusicEventListener::setMusicPlayEventCallback(const MusicPlayEventCallback& callback)
{
  m_sound_play_event_callback = callback;
}

void MusicEventListener::setMusicControlEventCallback(const MusicControlEventCallback& callback)
{
  m_sound_control_event_callback = callback;
}

void MusicEventListener::invoke(const Event& event)
{
  invokeIfCasted<MusicPlayEvent>(event, m_sound_play_event_callback);
  invokeIfCasted<MusicControlEvent>(event, m_sound_control_event_callback);
}

} // namespace egnim::events




