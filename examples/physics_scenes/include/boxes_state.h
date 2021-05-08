#ifndef BOXES_STATE_H
#define BOXES_STATE_H

/* ----------------------------------- egnim -------------------------------- */
#include <egnim/engine/events/mouse_event_listener.h>
#include <egnim/engine/events/mouse_event.h>
/* ----------------------------------- egnim -------------------------------- */
#include <egnim/engine/scene/scene_state.h>
/* -------------------------------------------------------------------------- */

class BoxesState : public egnim::scene::SceneState
{
public:
  explicit BoxesState(egnim::core::StateStack& state_stack, egnim::core::Context& context);
  ~BoxesState() override;

private:
  void createBox(const sf::Vector2f& position);
  void createFloor(const sf::Vector2f& position);

private:
  void mouseButtonPressed(const egnim::events::MouseButtonPressedEvent& pressed_event);

  void onActive() override;
  void onInactive() override;

private:
  egnim::events::MouseEventListener m_mouse_listener;
};

#endif //BOXES_STATE_H
