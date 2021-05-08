/* ----------------------------------- egnim -------------------------------- */
#include <egnim/engine/core/context.h>
#include <egnim/engine/physics/physics_world.h>
#include <egnim/engine/physics/physics_body.h>
#include <egnim/engine/physics/physics_shape.h>
#include <egnim/engine/events/event_dispatcher.h>
#include <egnim/engine/scene/scene_node.h>
#include <egnim/engine/scene/sprite_node.h>
/* ----------------------------------- Local -------------------------------- */
#include "boxes_state.h"
/* -------------------------------------------------------------------------- */

BoxesState::BoxesState(egnim::core::StateStack& state_stack, egnim::core::Context& context) :
  egnim::scene::SceneState(state_stack, context)
{

}

BoxesState::~BoxesState() = default;

void BoxesState::createBox(const sf::Vector2f& position)
{
  // get needed values
  auto& scene_node = getSceneNode();
  auto& physics_world = scene_node.getPhysicsWorld();
  auto& texture = scene_node.getContext().getTextureHolder().get("box");

  // create sprite / physics_body / physics_shape for box
  auto box = std::make_unique<egnim::scene::SpriteNode>();
  auto physics_body = std::make_unique<egnim::physics::PhysicsBody>(physics_world,egnim::physics::PhysicsBody::Type::DynamicBody);
  auto physics_shape = std::make_unique<egnim::physics::PhysicsShapeBox>(
    sf::Vector2f(static_cast<float>(texture.getSize().x),
                      static_cast<float>(texture.getSize().y)), sf::Vector2f(0,0));

  // set shape properties
  physics_shape->setDensity(1.f);
  physics_shape->setFriction(0.7f);
  physics_shape->setRestitution(0.0f);
  physics_shape->setRestitutionThreshold(1.0f);

  // set body properties
  physics_body->attachPhysicsShape(std::move(physics_shape));

  // set node properties
  box->attachComponent(std::move(physics_body));
  box->setTexture(texture);
  box->setOrigin(static_cast<float>(texture.getSize().x) / 2.f, static_cast<float>(texture.getSize().y) / 2.f);
  box->setPosition(position);

  // attach node to scene
  scene_node.attachChild(std::move(box));
}

void BoxesState::createFloor(const sf::Vector2f& position)
{
  // get needed values
  auto& scene_node = getSceneNode();
  auto& physics_world = scene_node.getPhysicsWorld();
  auto& texture = scene_node.getContext().getTextureHolder().get("floor");

  // create sprite / physics_body / physics_shape for box
  auto floor = std::make_unique<egnim::scene::SpriteNode>();
  auto physics_body = std::make_unique<egnim::physics::PhysicsBody>(physics_world,egnim::physics::PhysicsBody::Type::StaticBody);
  auto physics_shape = std::make_unique<egnim::physics::PhysicsShapeBox>(
    sf::Vector2f(static_cast<float>(texture.getSize().x),
                 static_cast<float>(texture.getSize().y)), sf::Vector2f(0,0));

  // set shape properties
  physics_shape->setDensity(0.f);
  physics_shape->setFriction(0.2f);
  physics_shape->setRestitution(0.0f);
  physics_shape->setRestitutionThreshold(1.0f);

  // set body properties
  physics_body->attachPhysicsShape(std::move(physics_shape));

  // set node properties
  floor->attachComponent(std::move(physics_body));
  floor->setTexture(texture);
  floor->setOrigin(static_cast<float>(texture.getSize().x) / 2.f, static_cast<float>(texture.getSize().y) / 2.f);
  floor->setPosition(position);

  // attach node to scene
  scene_node.attachChild(std::move(floor));
}

void BoxesState::mouseButtonPressed(const egnim::events::MouseButtonPressedEvent& pressed_event)
{
  if(pressed_event.getButton() == sf::Mouse::Button::Left)
  {
    createBox(sf::Vector2f(static_cast<float>(pressed_event.getPosition().x),
                                  static_cast<float>(pressed_event.getPosition().y)));
  }
}

void BoxesState::onActive()
{
  // init resources
  getContext().getTextureHolder().loadFromFile("box", "box.png",
                                          sf::IntRect(5, 5, 22, 22));
  getContext().getTextureHolder().loadFromFile("floor", "floor.png",
                                          sf::IntRect(50, 50, 400, 50));

  // connect listener
  m_mouse_listener.setMouseButtonPressedEventCallback([this](auto&& event){ this->mouseButtonPressed(event); });
  getContext().getEventDispatcher().addEventListener(std::addressof(m_mouse_listener), -1);

  // init scene
  auto& scene_node = getSceneNode();
  auto& physics_world = scene_node.getPhysicsWorld();

  physics_world.setGravity(sf::Vector2f(0, 9.8f));
  createFloor(sf::Vector2f(300, 500));
}

void BoxesState::onInactive()
{
  // remove resources
  getContext().getTextureHolder().remove("box");
  getContext().getTextureHolder().remove("floor");

  // disconnect listener
  getContext().getEventDispatcher().removeEventListener(std::addressof(m_mouse_listener));
}


