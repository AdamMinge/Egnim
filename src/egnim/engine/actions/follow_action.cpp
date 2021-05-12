/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/actions/follow_action.h>
#include <egnim/engine/scene/node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::actions {

FollowAction::FollowAction(scene::Node* followed_node) :
  m_followed_node(followed_node),
  m_left_margin(0),
  m_right_margin(0),
  m_top_margin(0),
  m_bottom_margin(0)
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

void FollowAction::setMargins(float left_margin, float right_margin, float top_margin, float bottom_margin)
{
  m_left_margin = left_margin;
  m_right_margin = right_margin;
  m_top_margin = top_margin;
  m_bottom_margin = bottom_margin;
}

void FollowAction::setLeftMargin(float left_margin)
{
  m_left_margin = left_margin;
}

float FollowAction::getLeftMargin() const
{
  return m_left_margin;
}

void FollowAction::setRightMargin(float right_margin)
{
  m_right_margin = right_margin;
}

float FollowAction::getRightMargin() const
{
  return m_right_margin;
}

void FollowAction::setTopMargin(float top_margin)
{
  m_top_margin = top_margin;
}

float FollowAction::getTopMargin() const
{
  return m_top_margin;
}

void FollowAction::setBottomMargin(float bottom_margin)
{
  m_bottom_margin = bottom_margin;
}

float FollowAction::getBottomMargin() const
{
  return m_bottom_margin;
}

void FollowAction::update(sf::Time dt)
{
  auto target = getTarget();
  auto followed = getFollowed();
  assert(target && followed);

  target->setPosition(std::clamp(target->getPosition().x, followed->getPosition().x - getLeftMargin(),
                                 followed->getPosition().x + getRightMargin()),
                      std::clamp(target->getPosition().y, followed->getPosition().y - getTopMargin(),
                                 followed->getPosition().y + getBottomMargin()));
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