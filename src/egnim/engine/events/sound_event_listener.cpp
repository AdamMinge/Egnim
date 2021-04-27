/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/sound_event_listener.h>
#include <egnim/engine/events/sound_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::event {

SoundEventListener::SoundEventListener() :
  EventListener(static_cast<int32_t>(Event::Type::Sound))
{

}

SoundEventListener::~SoundEventListener() = default;

void SoundEventListener::setSoundPlayEventCallback(const SoundPlayEventCallback& callback)
{
  m_sound_play_event_callback = callback;
}

void SoundEventListener::setSoundControlEventCallback(const SoundControlEventCallback& callback)
{
  m_sound_control_event_callback = callback;
}

void SoundEventListener::invoke(const Event& event)
{
  invokeIfCasted<SoundPlayEvent>(event, m_sound_play_event_callback);
  invokeIfCasted<SoundControlEvent>(event, m_sound_control_event_callback);
}

} // namespace egnim::event


