/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/actions/follow_action.h>
#include <egnim/engine/scene/node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::actions {

FollowAction::FollowAction(scene::Node* followed_node) :
  m_followed_node(followed_node)
{

}

FollowAction::~FollowAction() = default;

void FollowAction::setFollowed(scene::Node* followed_node)
{
  m_followed_node = followed_node;
}

scene::Node* FollowAction::getFollowed() const
{
  return m_followed_node;
}

void FollowAction::setBoundary(const sf::FloatRect& rect)
{
  m_rect = rect;
}

const sf::FloatRect& FollowAction::getBoundary() const
{
  return m_rect;
}

void FollowAction::setOffset(const sf::Vector2f& offset)
{
  m_offset = offset;
}

const sf::Vector2f& FollowAction::getOffset() const
{
  return m_offset;
}

void FollowAction::update(sf::Time dt)
{
  auto target = getTarget();
  auto followed = getFollowed();
  assert(target && followed);

  if(m_rect != sf::FloatRect())
  {
    auto boundary = sf::FloatRect(
      m_rect.left + target->getPosition().x,
      m_rect.height + target->getPosition().y,
      m_rect.width, m_rect.height);

    if(boundary.contains(followed->getPosition()))
      return;

    static_assert(false, "Not implemented yet");
  }
  else
  {
    target->setPosition(followed->getPosition() - m_offset);
  }
}

bool FollowAction::isDone() const
{
  return false;
}

std::unique_ptr<Action> FollowAction::clone() const
{
  auto clone_action = std::make_unique<FollowAction>(m_followed_node);
  Action::initializeClone(*clone_action);

  return clone_action;
}

} // namespace egnim::actions