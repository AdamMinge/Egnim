/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/scene_node.h>
#include <egnim/engine/core/command.h>
#include <egnim/engine/scene/component_container.h>
#include <egnim/engine/scene/component.h>
#include <egnim/engine/scene/camera.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{

Node::Node() :
  m_parent(nullptr),
  m_components(nullptr),
  m_camera_mask(Camera::CameraFlag::DEFAULT)
{

}

Node::~Node() = default;

void Node::attachChild(std::unique_ptr<Node> node)
{
  node->m_parent = this;
  m_children.push_back(std::move(node));
}

std::unique_ptr<Node> Node::detachChild(const Node &node)
{
  auto found = std::find_if(m_children.begin(), m_children.end(), [&node](auto &child)
  {
    return child.get() == &node;
  });

  if (found == m_children.end())
    return nullptr;

  auto child = std::move(*found);
  child->m_parent = nullptr;
  m_children.erase(found);
  return child;
}

void Node::attachComponent(std::unique_ptr<Component> component)
{
  if(!m_components)
    m_components = std::make_unique<ComponentContainer>(*this);

  m_components->add(std::move(component));
}

std::unique_ptr<Component> Node::attachComponent(const Component &component)
{
  auto comp = m_components ? m_components->remove(component) : nullptr;

  if(m_components && m_components->empty())
    m_components.reset();

  return comp;
}

void Node::setCameraMask(size_t mask, bool applyChildren)
{
  m_camera_mask = mask;

  if(applyChildren)
  {
    for (const auto &child : m_children)
      child->setCameraMask(mask, applyChildren);
  }
}

size_t Node::getCameraMask() const
{
  return m_camera_mask;
}

sf::Vector2f Node::getWorldPosition() const
{
  return getWorldTransform() * sf::Vector2f{};
}

sf::Transform Node::getWorldTransform() const
{
  auto transform = sf::Transform::Identity;
  for (const Node *node = this; node != nullptr; node = node->m_parent)
    transform = node->getTransform() * transform;

  return transform;
}

void Node::update(core::CommandQueue &command_queue, sf::Time dt)
{
  updateComponents(dt);
  updateCurrent(command_queue, dt);
  updateChildren(command_queue, dt);
}

void Node::onCommand(const core::Command &command, sf::Time dt)
{
  command(*this, dt);
  for (const auto &child : m_children)
    child->onCommand(command, dt);
}

void Node::updateCurrent(core::CommandQueue &command_queue, sf::Time dt)
{}

void Node::updateChildren(core::CommandQueue &command_queue, sf::Time dt)
{
  for (const auto &child : m_children)
    child->update(command_queue, dt);
}

void Node::updateComponents(sf::Time dt)
{
  if(m_components)
    m_components->update(dt);
}

void Node::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  states.transform *= getTransform();

  if(isVisibleByTarget(target))
    drawCurrent(target, states);

  drawChildren(target, states);
}

void Node::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {}

void Node::drawChildren(sf::RenderTarget &target, sf::RenderStates states) const
{
  for (const auto &child : m_children)
    child->draw(target, states);
}

bool Node::isVisibleByTarget(sf::RenderTarget& target) const
{
  auto target_camera = Camera::getActiveCamera(target);
  return target_camera == nullptr || target_camera->getViewFlag() & m_camera_mask;
}

} // namespace egnim::scene
