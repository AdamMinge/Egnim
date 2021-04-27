#ifndef SOUND_EVENT_LISTENER_H
#define SOUND_EVENT_LISTENER_H

/* --------------------------------- Standard ------------------------------- */
#include <functional>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/events/event_listener.h>
/* -------------------------------------------------------------------------- */

namespace egnim::event
{

  class SoundPlayEvent;
  class SoundControlEvent;

  class EGNIM_UTILITY_API SoundEventListener : public EventListener
  {
    EGNIM_CLASS(SoundEventListener, EventListener)

  public:
    using SoundPlayEventCallback = std::function<void(const SoundPlayEvent&)>;
    using SoundControlEventCallback = std::function<void(const SoundControlEvent&)>;

  public:
    explicit SoundEventListener();
    ~SoundEventListener() override;

    void setSoundPlayEventCallback(const SoundPlayEventCallback& callback);
    void setSoundControlEventCallback(const SoundControlEventCallback& callback);

  protected:
    void invoke(const Event& event) override;

  private:
    SoundPlayEventCallback m_sound_play_event_callback;
    SoundControlEventCallback m_sound_control_event_callback;
  };

} // namespace egnim::event

#endif //SOUND_EVENT_LISTENER_H
