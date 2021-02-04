/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/scene_node.h>
#include <egnim/engine/core/command.h>
/* -------------------------------------------------------------------------- */

namespace core {

SceneNode::SceneNode() :
  m_parent(nullptr)
{

}

SceneNode::~SceneNode() = default;

void SceneNode::attachChild(std::unique_ptr<SceneNode> node)
{
  node->m_parent = this;
  m_children.push_back(std::move(node));
}

std::unique_ptr<SceneNode> SceneNode::detachChild(const SceneNode& node)
{
  auto found = std::find_if(m_children.begin(), m_children.end(), [&node](auto& child){
    return child.get() == &node;
  });

  if(found == m_children.end())
    return nullptr;

  auto child = std::move(*found);
  child->m_parent = nullptr;
  m_children.erase(found);
  return child;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
  return getWorldTransform() * sf::Vector2f{};
}

sf::Transform SceneNode::getWorldTransform() const
{
  auto transform = sf::Transform::Identity;
  for(const SceneNode* node = this; node != nullptr; node = node->m_parent)
    transform = node->getTransform() * transform;

  return transform;
}

void SceneNode::update(CommandQueue& command_queue, sf::Time dt)
{
  updateCurrent(command_queue, dt);
  updateChildren(command_queue, dt);
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
  command(*this, dt);
  for(const auto& child : m_children)
    child->onCommand(command, dt);
}

void SceneNode::updateCurrent(CommandQueue& command_queue, sf::Time dt) {}

void SceneNode::updateChildren(CommandQueue& command_queue, sf::Time dt)
{
  for(const auto& child : m_children)
    child->update(command_queue, dt);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  drawCurrent(target, states);
  drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
  for(const auto& child : m_children)
    child->draw(target, states);
}

} // namespace cire
