#ifndef MUSIC_EVENT_LISTENER_H
#define MUSIC_EVENT_LISTENER_H

/* --------------------------------- Standard ------------------------------- */
#include <functional>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/events/event_listener.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events
{

  class MusicPlayEvent;
  class MusicControlEvent;

  class EGNIM_UTILITY_API MusicEventListener : public EventListener
  {
    EGNIM_CLASS(MusicEventListener, EventListener)

  public:
    using MusicPlayEventCallback = std::function<void(const MusicPlayEvent&)>;
    using MusicControlEventCallback = std::function<void(const MusicControlEvent&)>;

  public:
    explicit MusicEventListener();
    ~MusicEventListener() override;

    void setMusicPlayEventCallback(const MusicPlayEventCallback& callback);
    void setMusicControlEventCallback(const MusicControlEventCallback& callback);

  protected:
    void invoke(const Event& event) override;

  private:
    MusicPlayEventCallback m_sound_play_event_callback;
    MusicControlEventCallback m_sound_control_event_callback;
  };

} // namespace egnim::events

#endif //MUSIC_EVENT_LISTENER_H
