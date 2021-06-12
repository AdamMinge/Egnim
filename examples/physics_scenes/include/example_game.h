#ifndef EXAMPLE_GAME_H
#define EXAMPLE_GAME_H

/* --------------------------------- Standard ------------------------------- */
#include <map>
#include <functional>
/* ----------------------------------- egnim -------------------------------- */
#include <egnim/engine/core/game.h>
#include <egnim/engine/events/state_event_listener.h>
#include <egnim/engine/events/keyboard_event_listener.h>
#include <egnim/engine/events/state_event.h>
#include <egnim/engine/events/keyboard_event.h>
/* -------------------------------------------------------------------------- */

class ExampleGame
{
public:
  explicit ExampleGame(unsigned window_width, unsigned window_height, std::string window_title);
  ~ExampleGame();

  bool run();

private:
  void activatedState(const egnim::events::ActivatedState& activated_state_event);
  void keyboardKeyPressed(const egnim::events::KeyboardKeyPressedEvent& key_pressed_event);

private:
  std::string m_window_title;
  egnim::core::Game m_game;
  egnim::events::StateEventListener state_listener;
  egnim::events::KeyboardEventListener keyboard_listener;
};

#endif //EXAMPLE_GAME_H
