#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML//Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <list>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

  class EGNIM_UTILITY_API AnimatedSprite : public sf::Drawable, public sf::Transformable
  {
  public:
    explicit AnimatedSprite(const sf::Texture& texture, sf::Vector2i frame_size, sf::Time duration,
                            std::optional<std::size_t> num_frames = std::nullopt);
    ~AnimatedSprite() override;

    void update(sf::Time dt);

    void setFrameSize(sf::Vector2i frame_size);
    sf::Vector2i getFrameSize() const;

    void setNumFrames(std::size_t num_frames);
    std::size_t getNumFrames() const;

    void setDuration(sf::Time duration);
    sf::Time getDuration() const;

    void setRepeating(bool repeating = true);
    bool isRepeating() const;

    void setReversing(bool reverse = true);
    bool isReversing() const;

    bool isFinished() const;

    void restart();

    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;

  protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  private:
    void nextFrame();

  private:
    sf::Sprite m_sprite;
    sf::Vector2i m_frame_size;
    std::size_t m_num_frames;
    std::size_t m_current_frame;
    sf::Time m_duration;
    sf::Time m_elapsed_time;
    bool m_repeat;
    bool m_reverse;
  };

} // namespace egnim::core

#endif //ANIMATED_SPRITE_H
