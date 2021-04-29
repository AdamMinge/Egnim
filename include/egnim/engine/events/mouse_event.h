#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/events/event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events
{

  class EGNIM_UTILITY_API MousePositionEvent: public Event
  {
    EGNIM_CLASS(MousePositionEvent, Event)

  public:
    ~MousePositionEvent() override;

    void setPosition(const sf::Vector2i& position);
    [[nodiscard]] const sf::Vector2i& getPosition() const;

  protected:
    explicit MousePositionEvent(const sf::Vector2i& position);

  private:
    sf::Vector2i m_position;
  };

  class EGNIM_UTILITY_API MouseEnteredEvent: public MousePositionEvent
  {
    EGNIM_CLASS(MousePositionEvent, MousePositionEvent)

  public:
    explicit MouseEnteredEvent(const sf::Vector2i& position);
    ~MouseEnteredEvent() override;
  };

  class EGNIM_UTILITY_API MouseLeftEvent: public MousePositionEvent
  {
    EGNIM_CLASS(MousePositionEvent, MousePositionEvent)

  public:
    explicit MouseLeftEvent(const sf::Vector2i& position);
    ~MouseLeftEvent() override;
  };

  class EGNIM_UTILITY_API MouseMoveEvent: public MousePositionEvent
  {
  EGNIM_CLASS(MouseMoveEvent, MousePositionEvent)

  public:
    explicit MouseMoveEvent(const sf::Vector2i& position);
    ~MouseMoveEvent() override;
  };

  class EGNIM_UTILITY_API MouseButtonPressedEvent: public MousePositionEvent
  {
    EGNIM_CLASS(MouseButtonPressedEvent, MousePositionEvent)

  public:
    explicit MouseButtonPressedEvent(sf::Mouse::Button button, const sf::Vector2i& position);
    ~MouseButtonPressedEvent() override;

    void setButton(sf::Mouse::Button button);
    [[nodiscard]] sf::Mouse::Button getButton() const;

  private:
    sf::Mouse::Button m_button;
  };

  class EGNIM_UTILITY_API MouseButtonReleasedEvent: public MousePositionEvent
  {
    EGNIM_CLASS(MouseButtonReleasedEvent, MousePositionEvent)

  public:
    explicit MouseButtonReleasedEvent(sf::Mouse::Button button, const sf::Vector2i& position);
    ~MouseButtonReleasedEvent() override;

    void setButton(sf::Mouse::Button button);
    [[nodiscard]] sf::Mouse::Button getButton() const;

  private:
    sf::Mouse::Button m_button;
  };

  class EGNIM_UTILITY_API MouseWheelScrollEvent: public MousePositionEvent
  {
    EGNIM_CLASS(MouseWheelScrollEvent, MousePositionEvent)

  public:
    explicit MouseWheelScrollEvent(sf::Mouse::Wheel wheel, float delta, const sf::Vector2i& position);
    ~MouseWheelScrollEvent() override;

    void setWheel(sf::Mouse::Wheel wheel);
    [[nodiscard]] sf::Mouse::Wheel getWheel() const;

    void setDelta(float delta);
    [[nodiscard]] float getDelta() const;

  private:
    sf::Mouse::Wheel m_wheel;
    float m_delta;
  };

}; // namespace egnim::events

#endif //MOUSE_EVENT_H
