#ifndef BOXES_STATE_H
#define BOXES_STATE_H

/* ----------------------------------- egnim -------------------------------- */
#include <egnim/engine/events/keyboard_event_listener.h>
#include <egnim/engine/events/mouse_event_listener.h>
#include <egnim/engine/events/window_event_listener.h>
#include <egnim/engine/events/keyboard_event.h>
#include <egnim/engine/events/mouse_event.h>
#include <egnim/engine/events/window_event.h>
#include <egnim/engine/physics/physics_material.h>
#include <egnim/engine/physics/physics_body.h>
#include <egnim/engine/scene/sprite_node.h>
#include <egnim/engine/scene/camera_node.h>
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
  void createCamera(const sf::Vector2f& position, const sf::FloatRect& rect, std::string_view name);

  std::unique_ptr<egnim::scene::SpriteNode> createSpriteNode(const sf::Vector2f& position,
                                                             const sf::Texture& texture,
                                                             const egnim::physics::PhysicsMaterial& material,
                                                             egnim::physics::PhysicsBody::Type type);

private:
  void mouseButtonPressed(const egnim::events::MouseButtonPressedEvent& pressed_button_event);
  void keyboardKeyPressed(const egnim::events::KeyboardKeyPressedEvent& pressed_key_event);
  void windowResized(const egnim::events::WindowResizeEvent& window_resize_event);

  void onActive() override;
  void onInactive() override;

private:
  egnim::events::MouseEventListener m_mouse_listener;
  egnim::events::KeyboardEventListener m_keyboard_listener;
  egnim::events::WindowEventListener m_window_listener;
};

#endif //BOXES_STATE_H
