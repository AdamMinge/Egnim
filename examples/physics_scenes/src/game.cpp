/* ----------------------------------- egnim -------------------------------- */
#include <egnim/engine/core/context.h>
#include <egnim/engine/core/state_stack.h>
#include <egnim/engine/events/event_dispatcher.h>
/* ----------------------------------- Local -------------------------------- */
#include "game.h"
#include "boxes_state.h"
/* -------------------------------------------------------------------------- */

Game::Game(unsigned window_width, unsigned window_height, std::string window_title) :
  m_window_title(std::move(window_title))
{
  // create window
  m_main_loop.getContext().getRenderWindow().create(
    sf::VideoMode(window_width, window_height), m_window_title);

  // create listeners and attach them to dispatcher
  state_listener.setActivatedStateCallback([this](auto&& event){ this->activatedState(event); });
  m_main_loop.getContext().getEventDispatcher().addEventListener(std::addressof(state_listener), -1);

  keyboard_listener.setKeyboardKeyPressedEventCallback([this](auto&& event){ this->keyboardKeyPressed(event); });
  m_main_loop.getContext().getEventDispatcher().addEventListener(std::addressof(keyboard_listener), -1);

  // register states
  m_main_loop.getStateStack().registerState<BoxesState>("boxes_state", m_main_loop.getContext());

  // set first state
  m_main_loop.getStateStack().pushState("boxes_state");
}

Game::~Game() = default;

bool Game::run()
{
  m_main_loop.run();
  return true;
}

void Game::activatedState(const egnim::events::ActivatedState& activated_state_event)
{
  // set window title depend on activated state
  auto state_id = std::string(activated_state_event.getStateId());
  m_main_loop.getContext().getRenderWindow().setTitle(m_window_title + " [" + state_id + "]");
}

void Game::keyboardKeyPressed(const egnim::events::KeyboardKeyPressedEvent& key_pressed_event)
{
  switch(key_pressed_event.getKey())
  {
    case sf::Keyboard::Num1:
      m_main_loop.getStateStack().popState();
      m_main_loop.getStateStack().pushState("boxes_state");
      break;

    default:
      break;
  }
}