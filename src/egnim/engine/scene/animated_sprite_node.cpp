/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderTarget.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/animated_sprite_node.h>
#include <egnim/engine/scene/scene_visitor.h>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{

std::unique_ptr<AnimatedSpriteNode> AnimatedSpriteNode::create()
{
  return std::unique_ptr<AnimatedSpriteNode>(new (std::nothrow) AnimatedSpriteNode);
}

AnimatedSpriteNode::AnimatedSpriteNode() :
  m_current_animation(m_animated_sprites.end())
{

}

AnimatedSpriteNode::~AnimatedSpriteNode() = default;

void AnimatedSpriteNode::addAnimation(std::string_view id, graphics::AnimatedSprite&& animated_sprite)
{
  assert(!m_animated_sprites.contains(id));
  m_animated_sprites.emplace(std::make_pair(id, std::move(animated_sprite)));
}

void AnimatedSpriteNode::removeAnimation(std::string_view id)
{
  assert(m_animated_sprites.contains(id));

  if(m_current_animation->first == id)
    m_current_animation = m_animated_sprites.end();

  m_animated_sprites.erase(id);
}

void AnimatedSpriteNode::setCurrentAnimation(std::string_view id)
{
  assert(m_animated_sprites.contains(id));
  m_current_animation = m_animated_sprites.find(id);
}

std::string_view AnimatedSpriteNode::getCurrentAnimation()
{
  if(m_current_animation != m_animated_sprites.end())
    return m_current_animation->first;
  else
    return std::string_view{};
}

void AnimatedSpriteNode::accept(SceneVisitor& visitor)
{
  visitor.visitAnimatedSpriteNode(*this);
}

void AnimatedSpriteNode::updateCurrent(sf::Time dt)
{
  if(m_current_animation != m_animated_sprites.end())
    m_current_animation->second.update(dt);
}

void AnimatedSpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
  if(m_current_animation != m_animated_sprites.end())
    target.draw(m_current_animation->second, states);
}

} // namespace egnim::scene