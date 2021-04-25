#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

/* --------------------------------- Standard ------------------------------- */
#include <functional>
#include <cstdint>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/core/object.h>
/* -------------------------------------------------------------------------- */

namespace egnim::event
{

  class EventDispatcher;
  class Event;

  class EGNIM_UTILITY_API EventListener : public core::Object
  {
    EGNIM_CLASS(EventListener, core::Object)
    friend class EventDispatcher;

  public:
    ~EventListener() override;

    [[nodiscard]] int32_t getListenEvents() const;

    void setEnabled(bool enabled);
    [[nodiscard]] bool isEnabled() const;

    [[nodiscard]] EventDispatcher* getEventDispatcher();
    [[nodiscard]] const EventDispatcher* getEventDispatcher() const;

  protected:
    explicit EventListener(int32_t listen_events, std::function<void(Event&)> on_event);

    void setEventDispatcher(EventDispatcher* event_dispatcher);

  private:
    int32_t m_listen_events;
    std::function<void(Event&)> m_on_event;
    EventDispatcher* m_event_dispatcher;
    bool m_enabled;
  };

} // namespace egnim::event

#endif //EVENT_LISTENER_H
