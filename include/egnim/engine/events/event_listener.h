#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

/* --------------------------------- Standard ------------------------------- */
#include <functional>
#include <cstdint>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/core/object.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events
{

  namespace priv { class EventListenerVector; }
  class EventDispatcher;
  class Event;

  class EGNIM_UTILITY_API EventListener : public core::Object
  {
    EGNIM_CLASS(EventListener, core::Object)
    friend class priv::EventListenerVector;
    friend class EventDispatcher;

  public:
    ~EventListener() override;

    [[nodiscard]] int32_t getListenEvents() const;

    void setEnabled(bool enabled);
    [[nodiscard]] bool isEnabled() const;

    [[nodiscard]] EventDispatcher* getEventDispatcher();
    [[nodiscard]] const EventDispatcher* getEventDispatcher() const;

  protected:
    explicit EventListener(int32_t listen_events);

    virtual void invoke(const Event& event) = 0;
    void setEventDispatcher(EventDispatcher* event_dispatcher);

    template<typename EVENT_TO_CAST>
    bool invokeIfCasted(const Event& event, const std::function<void(const EVENT_TO_CAST)>& invoke);

  private:
    int32_t m_listen_events;
    EventDispatcher* m_event_dispatcher;
    bool m_enabled;
  };

  template<typename EVENT_TO_CAST>
  bool EventListener::invokeIfCasted(const Event& event, const std::function<void(const EVENT_TO_CAST)>& invoke)
  {
    auto sound_play_event = dynamic_cast<const EVENT_TO_CAST*>(std::addressof(event));
    if(sound_play_event && invoke)
      invoke(*sound_play_event);

    return sound_play_event;
  }

} // namespace egnim::events

#endif //EVENT_LISTENER_H
