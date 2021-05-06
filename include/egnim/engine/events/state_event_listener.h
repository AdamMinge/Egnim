#ifndef STATE_EVENT_LISTENER_H
#define STATE_EVENT_LISTENER_H

/* --------------------------------- Standard ------------------------------- */
#include <functional>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/events/event_listener.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events
{

  class ActivatedState;
  class InactivatedState;

  class EGNIM_UTILITY_API StateEventListener: public EventListener
  {
    EGNIM_CLASS(StateEventListener, EventListener)

  public:
    using ActivatedStateCallback = std::function<void(const ActivatedState&)>;
    using InactivatedStateCallback = std::function<void(const InactivatedState&)>;

  public:
    explicit StateEventListener();
    ~StateEventListener() override;

    void setActivatedStateCallback(const ActivatedStateCallback& callback);
    void setInactivatedStateCallback(const InactivatedStateCallback& callback);

  protected:
    void invoke(const Event& event) override;

  private:
    ActivatedStateCallback m_activated_state_event_callback;
    InactivatedStateCallback m_inactivated_state_event_callback;
  };

} // namespace egnim::events

#endif //STATE_EVENT_LISTENER_H
