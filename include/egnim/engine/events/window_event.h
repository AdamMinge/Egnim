#ifndef WINDOW_EVENT_H
#define WINDOW_EVENT_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/events/event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events
{

  class EGNIM_UTILITY_API WindowGainedFocusEvent: public Event
  {
    EGNIM_CLASS(WindowGainedFocusEvent, Event)

  public:
    explicit WindowGainedFocusEvent();
    ~WindowGainedFocusEvent() override;
  };

  class EGNIM_UTILITY_API WindowLostFocusEvent: public Event
  {
    EGNIM_CLASS(WindowLostFocusEvent, Event)

  public:
    explicit WindowLostFocusEvent();
    ~WindowLostFocusEvent() override;
  };

  class EGNIM_UTILITY_API WindowCloseEvent: public Event
  {
    EGNIM_CLASS(WindowCloseEvent, Event)

  public:
    explicit WindowCloseEvent();
    ~WindowCloseEvent() override;
  };

  class EGNIM_UTILITY_API WindowResizeEvent: public Event
  {
    EGNIM_CLASS(WindowResizeEvent, Event)

  public:
    explicit WindowResizeEvent(const sf::Vector2u& size);
    ~WindowResizeEvent() override;

    void setSize(const sf::Vector2u& size);
    [[nodiscard]] const sf::Vector2u& getSize() const;

  private:
    sf::Vector2u m_size;
  };

} // namespace egnim::events

#endif //WINDOW_EVENT_H
