/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Clock.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/main_loop.h>
#include <egnim/engine/core/state_stack.h>
#include <egnim/engine/core/context.h>
#include <egnim/engine/events/event_dispatcher.h>
#include <egnim/engine/events/keyboard_event.h>
#include <egnim/engine/events/mouse_event.h>
#include <egnim/engine/events/window_event.h>
#include <egnim/engine/events/joystick_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core {

MainLoop::MainLoop() :
  m_context(std::make_unique<Context>()),
  m_states(std::make_unique<StateStack>(*m_context)),
  m_time_per_frame(sf::seconds(1.f/60.f))
{

}

MainLoop::~MainLoop() = default;

void MainLoop::setTimePerFrame(const sf::Time& time_per_frame)
{
  m_time_per_frame = time_per_frame;
}

sf::Time MainLoop::getTimePerFrame() const
{
  return m_time_per_frame;
}

Context& MainLoop::getContext()
{
  return *m_context;
}

const Context& MainLoop::getContext() const
{
  return *m_context;
}

StateStack& MainLoop::getStateStack()
{
  return *m_states;
}

const StateStack& MainLoop::getStateStack() const
{
  return *m_states;
}

void MainLoop::run()
{
  sf::Clock clock;
  sf::Time time_since_last_update = sf::Time::Zero;
  auto& render_window = m_context->getRenderWindow();

  while(render_window.isOpen())
  {
    sf::Time dt = clock.restart();
    time_since_last_update += dt;

    while(time_since_last_update > m_time_per_frame)
    {
      time_since_last_update -= m_time_per_frame;

      processInput();
      update(m_time_per_frame);

      if(m_states->empty())
        render_window.close();
    }

    render();
  }
}

void MainLoop::processInput()
{
  sf::Event event{};
  auto& render_window = m_context->getRenderWindow();

  while(render_window.pollEvent(event))
  {
    processWindowEvent(event);
    processKeyboardEvent(event);
    processMouseEvent(event);
    processJoystickEvent(event);
  }
}

void MainLoop::update(sf::Time dt)
{
  m_states->update(dt);
}

void MainLoop::render()
{
  auto& render_window = m_context->getRenderWindow();

  render_window.clear();
  m_states->draw();
  render_window.display();
}

void MainLoop::processWindowEvent(const sf::Event& window_event)
{
  switch(window_event.type)
  {
    case sf::Event::GainedFocus:
    {
      auto window_gained_focus_event = events::WindowGainedFocusEvent();
      m_context->getEventDispatcher().dispatchEvent(window_gained_focus_event);
      break;
    }

    case sf::Event::LostFocus:
    {
      auto window_lost_focus_event = events::WindowLostFocusEvent();
      m_context->getEventDispatcher().dispatchEvent(window_lost_focus_event);
      break;
    }

    case sf::Event::Closed:
    {
      auto window_close_event = events::WindowCloseEvent();
      m_context->getEventDispatcher().dispatchEvent(window_close_event);
      break;
    }

    case sf::Event::Resized:
    {
      auto window_resize_event = events::WindowResizeEvent(
        sf::Vector2u(window_event.size.width, window_event.size.height));
      m_context->getEventDispatcher().dispatchEvent(window_resize_event);
      break;
    }

    default:
      break;
  }
}

void MainLoop::processKeyboardEvent(const sf::Event& keyboard_event)
{
  switch(keyboard_event.type)
  {
    case sf::Event::KeyPressed:
    {
      auto key_pressed_event = events::KeyboardKeyPressedEvent(keyboard_event.key.code);
      key_pressed_event.setAltPressed(keyboard_event.key.alt);
      key_pressed_event.setControlPressed(keyboard_event.key.control);
      key_pressed_event.setShiftPressed(keyboard_event.key.shift);
      key_pressed_event.setSystemPressed(keyboard_event.key.system);

      m_context->getEventDispatcher().dispatchEvent(key_pressed_event);
      break;
    }

    case sf::Event::KeyReleased:
    {
      auto key_released_event = events::KeyboardKeyReleasedEvent(keyboard_event.key.code);
      key_released_event.setAltPressed(keyboard_event.key.alt);
      key_released_event.setControlPressed(keyboard_event.key.control);
      key_released_event.setShiftPressed(keyboard_event.key.shift);
      key_released_event.setSystemPressed(keyboard_event.key.system);

      m_context->getEventDispatcher().dispatchEvent(key_released_event);
      break;
    }

    default:
      break;
  }
}

void MainLoop::processMouseEvent(const sf::Event& mouse_event)
{
  switch(mouse_event.type)
  {
    case sf::Event::MouseButtonPressed:
    {
      auto mouse_button_pressed_event = events::MouseButtonPressedEvent(
        mouse_event.mouseButton.button,sf::Vector2i(mouse_event.mouseButton.x, mouse_event.mouseButton.y));

      m_context->getEventDispatcher().dispatchEvent(mouse_button_pressed_event);
      break;
    }

    case sf::Event::MouseButtonReleased:
    {
      auto mouse_button_released_event = events::MouseButtonReleasedEvent(
        mouse_event.mouseButton.button,sf::Vector2i(mouse_event.mouseButton.x, mouse_event.mouseButton.y));

      m_context->getEventDispatcher().dispatchEvent(mouse_button_released_event);
      break;
    }

    case sf::Event::MouseEntered:
    {
      auto mouse_entered_event = events::MouseEnteredEvent(
        sf::Vector2i(sf::Mouse::getPosition(m_context->getRenderWindow())));

      m_context->getEventDispatcher().dispatchEvent(mouse_entered_event);
      break;
    }

    case sf::Event::MouseLeft:
    {
      auto mouse_left_event = events::MouseLeftEvent(
        sf::Vector2i(sf::Mouse::getPosition(m_context->getRenderWindow())));

      m_context->getEventDispatcher().dispatchEvent(mouse_left_event);
      break;
    }

    case sf::Event::MouseMoved:
    {
      auto mouse_move_event = events::MouseMoveEvent(
        sf::Vector2i(mouse_event.mouseMove.x, mouse_event.mouseMove.y));

      m_context->getEventDispatcher().dispatchEvent(mouse_move_event);
      break;
    }

    case sf::Event::MouseWheelScrolled:
    {
      auto mouse_wheel_scrolled_event = events::MouseWheelScrollEvent(
        mouse_event.mouseWheelScroll.wheel, mouse_event.mouseWheelScroll.delta,
        sf::Vector2i(mouse_event.mouseWheelScroll.x, mouse_event.mouseWheelScroll.y));

      m_context->getEventDispatcher().dispatchEvent(mouse_wheel_scrolled_event);
      break;
    }

    default:
      break;
  }
}

void MainLoop::processJoystickEvent(const sf::Event& joystick_event)
{
  switch(joystick_event.type)
  {
    case sf::Event::JoystickButtonPressed:
    {
      auto joystick_button_pressed_event = events::JoystickButtonPressedEvent(joystick_event.joystickButton.joystickId,
                                                                              joystick_event.joystickButton.button);

      m_context->getEventDispatcher().dispatchEvent(joystick_button_pressed_event);
      break;
    }

    case sf::Event::JoystickButtonReleased:
    {
      auto joystick_button_released_event = events::JoystickButtonReleasedEvent(joystick_event.joystickButton.joystickId,
                                                                               joystick_event.joystickButton.button);

      m_context->getEventDispatcher().dispatchEvent(joystick_button_released_event);
      break;
    }

    case sf::Event::JoystickConnected:
    {
      auto joystick_connected_event = events::JoystickConnectedEvent(joystick_event.joystickConnect.joystickId);
      m_context->getEventDispatcher().dispatchEvent(joystick_connected_event);
      break;
    }

    case sf::Event::JoystickDisconnected:
    {
      auto joystick_disconnected_event = events::JoystickDisconnectedEvent(joystick_event.joystickConnect.joystickId);
      m_context->getEventDispatcher().dispatchEvent(joystick_disconnected_event);
      break;
    }

    case sf::Event::JoystickMoved:
    {
      auto joystick_move_event = events::JoystickMoveEvent(joystick_event.joystickMove.joystickId,
                                                           joystick_event.joystickMove.axis,
                                                           joystick_event.joystickMove.position);

      m_context->getEventDispatcher().dispatchEvent(joystick_move_event);
      break;
    }

    default:
      break;
  }
}

} // namespace egnim::core
