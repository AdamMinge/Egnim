/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderTarget.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/animated_sprite_node.h>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

AnimatedSpriteNode::AnimatedSpriteNode() :
  m_current_animation(m_animated_sprites.end())
{

}

AnimatedSpriteNode::~AnimatedSpriteNode() = default;

void AnimatedSpriteNode::addAnimation(std::string_view id, AnimatedSprite&& animated_sprite)
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

void AnimatedSpriteNode::updateCurrent(CommandQueue &command_queue, sf::Time dt)
{
  if(m_current_animation != m_animated_sprites.end())
    m_current_animation->second.update(dt);
}

void AnimatedSpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
  if(m_current_animation != m_animated_sprites.end())
    target.draw(m_current_animation->second, states);
}

} // namespace egnim::core