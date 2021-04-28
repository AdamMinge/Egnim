#ifndef CONTACT_EVENT_LISTENER_H
#define CONTACT_EVENT_LISTENER_H

/* --------------------------------- Standard ------------------------------- */
#include <functional>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/events/event_listener.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events
{

  class BeginContactEvent;
  class EndContactEvent;
  class PreSolveContactEvent;
  class PostSolveContactEvent;

  class EGNIM_UTILITY_API ContactEventListener : public EventListener
  {
    EGNIM_CLASS(ContactEventListener, EventListener)

  public:
    using BeginContactEventCallback = std::function<void(const BeginContactEvent&)>;
    using EndContactEventCallback = std::function<void(const EndContactEvent&)>;
    using PreSolveContactEventCallback = std::function<void(const PreSolveContactEvent&)>;
    using PostSolveContactEventCallback = std::function<void(const PostSolveContactEvent&)>;

  public:
    explicit ContactEventListener();
    ~ContactEventListener() override;

    void setBeginContactEventCallback(const BeginContactEventCallback& callback);
    void setEndContactEventCallback(const EndContactEventCallback& callback);
    void setPreSolveContactEventCallback(const PreSolveContactEventCallback& callback);
    void setPostSolveContactEventCallback(const PostSolveContactEventCallback& callback);

  protected:
    void invoke(const Event& event) override;

  private:
    BeginContactEventCallback m_begin_contact_event_callback;
    EndContactEventCallback m_end_contact_event_callback;
    PreSolveContactEventCallback m_pre_solve_contact_event_callback;
    PostSolveContactEventCallback m_post_solve_contact_event_callback;
  };

} // namespace egnim::events

#endif //CONTACT_EVENT_LISTENER_H
