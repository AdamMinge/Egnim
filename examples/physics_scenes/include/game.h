#ifndef GAME_H
#define GAME_H

/* --------------------------------- Standard ------------------------------- */
#include <map>
#include <functional>
/* ----------------------------------- egnim -------------------------------- */
#include <egnim/engine/core/main_loop.h>
#include <egnim/engine/events/state_event_listener.h>
#include <egnim/engine/events/keyboard_event_listener.h>
#include <egnim/engine/events/state_event.h>
#include <egnim/engine/events/keyboard_event.h>
/* -------------------------------------------------------------------------- */

class Game
{
public:
  explicit Game(unsigned window_width, unsigned window_height, std::string window_title);
  ~Game();

  bool run();

private:
  void activatedState(const egnim::events::ActivatedState& activated_state_event);
  void keyboardKeyPressed(const egnim::events::KeyboardKeyPressedEvent& key_pressed_event);

private:
  std::string m_window_title;
  egnim::core::MainLoop m_main_loop;
  egnim::events::StateEventListener state_listener;
  egnim::events::KeyboardEventListener keyboard_listener;
};

#endif //GAME_H
