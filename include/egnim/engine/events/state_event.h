#ifndef STATE_EVENT_H
#define STATE_EVENT_H

/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/events/event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{
  class State;
}

namespace egnim::events
{

  class EGNIM_UTILITY_API StateEvent: public Event
  {
    EGNIM_CLASS(StateEvent, Event)

  public:
    ~StateEvent() override;

    void setState(core::State& state);
    [[nodiscard]] core::State& getState() const;

  protected:
    explicit StateEvent(core::State& state);

  private:
    core::State* m_state;
  };

  class EGNIM_UTILITY_API ActivatedState: public StateEvent
  {
    EGNIM_CLASS(ActivatedState, StateEvent)

  public:
    explicit ActivatedState(core::State& state);
    ~ActivatedState() override;
  };

  class EGNIM_UTILITY_API InactivatedState: public StateEvent
  {
    EGNIM_CLASS(InactivatedState, StateEvent)

  public:
    explicit InactivatedState(core::State& state);
    ~InactivatedState() override;
  };

}; // namespace egnim::events

#endif //STATE_EVENT_H
