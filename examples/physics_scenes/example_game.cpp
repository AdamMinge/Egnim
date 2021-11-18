/* ----------------------------------- egnim -------------------------------- */
#include <egnim/engine/core/context.h>
#include <egnim/engine/core/state_stack.h>
#include <egnim/engine/events/event_dispatcher.h>
/* ----------------------------------- Local -------------------------------- */
#include "physics_scenes/example_game.h"
#include "physics_scenes/boxes_state.h"
/* -------------------------------------------------------------------------- */

ExampleGame::ExampleGame(unsigned window_width, unsigned window_height, std::string window_title) :
  m_window_title(std::move(window_title))
{
  // create window
  m_game.getContext().getRenderWindow().create(
    sf::VideoMode(window_width, window_height), m_window_title);

  // create listeners and attach them to dispatcher
  state_listener.setActivatedStateCallback([this](auto&& event){ this->activatedState(event); });
  m_game.getContext().getEventDispatcher().addEventListener(std::addressof(state_listener), -1);

  keyboard_listener.setKeyboardKeyPressedEventCallback([this](auto&& event){ this->keyboardKeyPressed(event); });
  m_game.getContext().getEventDispatcher().addEventListener(std::addressof(keyboard_listener), -1);

  // register states
  m_game.getStateStack().registerState<BoxesState>("boxes_state", m_game.getContext());

  // set first state
  m_game.getStateStack().pushState("boxes_state");
}

ExampleGame::~ExampleGame() = default;

bool ExampleGame::run()
{
  m_game.run();
  return true;
}

void ExampleGame::activatedState(const egnim::events::ActivatedState& activated_state_event)
{
  // set window title depend on activated state
  auto state_id = std::string(activated_state_event.getStateId());
  m_game.getContext().getRenderWindow().setTitle(m_window_title + " [" + state_id + "]");
}

void ExampleGame::keyboardKeyPressed(const egnim::events::KeyboardKeyPressedEvent& key_pressed_event)
{
  switch(key_pressed_event.getKey())
  {
    case sf::Keyboard::Num1:
      m_game.getStateStack().popState();
      m_game.getStateStack().pushState("boxes_state");
      break;

    default:
      break;
  }
}