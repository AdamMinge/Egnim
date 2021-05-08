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

    void setStateId(std::string_view state_id);
    [[nodiscard]] std::string_view getStateId() const;

  protected:
    explicit StateEvent(core::State& state, std::string_view state_id);

  private:
    core::State* m_state;
    std::string_view m_state_id;
  };

  class EGNIM_UTILITY_API ActivatedState: public StateEvent
  {
    EGNIM_CLASS(ActivatedState, StateEvent)

  public:
    explicit ActivatedState(core::State& state, std::string_view state_id);
    ~ActivatedState() override;
  };

  class EGNIM_UTILITY_API InactivatedState: public StateEvent
  {
    EGNIM_CLASS(InactivatedState, StateEvent)

  public:
    explicit InactivatedState(core::State& state, std::string_view state_id);
    ~InactivatedState() override;
  };

}; // namespace egnim::events

#endif //STATE_EVENT_H
