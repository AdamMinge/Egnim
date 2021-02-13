/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderTarget.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/animated_sprite.h>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

AnimatedSprite::AnimatedSprite(const sf::Texture& texture, sf::Vector2i frame_size,
                               sf::Time duration, std::optional<std::size_t> num_frames) :
  m_sprite(texture),
  m_num_frames(0),
  m_current_frame(0),
  m_duration(duration),
  m_elapsed_time(sf::Time::Zero),
  m_repeat(false),
  m_reverse(false)
{
  setFrameSize(frame_size);

  if(num_frames.has_value())
    setNumFrames(num_frames.value());
  else
    setNumFrames(std::numeric_limits<size_t>::max());
}

AnimatedSprite::~AnimatedSprite() = default;

void AnimatedSprite::updateCurrent(sf::Time dt)
{
  auto time_per_frame = m_duration / static_cast<float>(m_num_frames);
  m_elapsed_time += dt;

  while(m_elapsed_time >= time_per_frame && !isFinished())
  {
    m_elapsed_time -= time_per_frame;
    nextFrame();
  }
}

void AnimatedSprite::setFrameSize(sf::Vector2i frame_size)
{
  assert(frame_size.x > 0 && frame_size.y > 0);

  auto& texture_rect = m_sprite.getTextureRect();
  m_frame_size.x = std::min(texture_rect.width, frame_size.x);
  m_frame_size.y = std::min(texture_rect.height, frame_size.y);
  restart();
}

sf::Vector2i AnimatedSprite::getFrameSize() const
{
  return m_frame_size;
}

void AnimatedSprite::setNumFrames(std::size_t num_frames)
{
  auto texture_bounds = m_sprite.getTexture()->getSize();
  auto max_num_frames = static_cast<std::size_t>(texture_bounds.x / m_frame_size.x) *
                                                (texture_bounds.y / m_frame_size.y);

  m_num_frames = std::min(max_num_frames, num_frames);
  restart();
}

std::size_t AnimatedSprite::getNumFrames() const
{
  return m_num_frames;
}

void AnimatedSprite::setDuration(sf::Time duration)
{
  m_duration = duration;
  restart();
}

sf::Time AnimatedSprite::getDuration() const
{
  return m_duration;
}

void AnimatedSprite::setRepeating(bool repeating)
{
  m_repeat = repeating;
  restart();
}

bool AnimatedSprite::isRepeating() const
{
  return m_repeat;
}

void AnimatedSprite::setReversing(bool reverse)
{
  m_reverse = reverse;
  restart();
}

bool AnimatedSprite::isReversing() const
{
  return m_reverse;
}

bool AnimatedSprite::isFinished() const
{
  return !m_repeat && m_reverse ? m_current_frame == 0 : m_current_frame == m_num_frames - 1;
}

void AnimatedSprite::restart()
{
  auto texture_bounds = m_sprite.getTexture()->getSize();
  auto texture_rect = sf::IntRect(texture_bounds.x - m_frame_size.x,
                                  texture_bounds.y - m_frame_size.y,
                                  m_frame_size.x, m_frame_size.y);

  m_elapsed_time = sf::Time::Zero;
  m_current_frame = (m_reverse) ? m_num_frames - 1 : 0;
  m_sprite.setTextureRect(texture_rect);
}

sf::FloatRect AnimatedSprite::getLocalBounds() const
{
  return sf::FloatRect(getOrigin(), static_cast<sf::Vector2f>(getFrameSize()));
}

sf::FloatRect AnimatedSprite::getGlobalBounds() const
{
  return getTransform().transformRect(getLocalBounds());
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(m_sprite, states);
}

void AnimatedSprite::nextFrame()
{
  auto texture_bounds = m_sprite.getTexture()->getSize();
  auto texture_rect = m_sprite.getTextureRect();

  if(m_reverse ? m_current_frame == 0 : m_current_frame == m_num_frames - 1)
  {
    if(m_repeat)
    {
      texture_rect = sf::IntRect(texture_bounds.x - m_frame_size.x,
                                 texture_bounds.y - m_frame_size.y,
                                 m_frame_size.x, m_frame_size.y);

      m_current_frame = m_reverse ? m_num_frames - 1 : 0;
    }
  }
  else
  {
    if(m_reverse)
    {
      texture_rect.left -= texture_rect.width;
      if(texture_rect.left < 0)
      {
        texture_rect.left = 0;
        texture_rect.top -= texture_rect.height;
      }

      --m_current_frame;
    }
    else
    {
      texture_rect.left += texture_rect.width;
      if(texture_rect.left > texture_bounds.x)
      {
        texture_rect.left = 0;
        texture_rect.top += texture_rect.height;
      }

      ++m_current_frame;
    }
  }

  m_sprite.setTextureRect(texture_rect);
}

} // namespace egnim::core