#ifndef SOUND_EVENT_H
#define SOUND_EVENT_H

/* --------------------------------- Standard ------------------------------- */
#include <optional>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/events/event.h>
#include <egnim/engine/scene/sound_node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::event
{

  class EGNIM_UTILITY_API SoundPlayEvent : public Event
  {
    EGNIM_CLASS(SoundPlayEvent, Event)

  public:
    explicit SoundPlayEvent(std::string_view sound_id, const sf::Vector2f& sound_position = sf::Vector2f(0, 0),
                            std::optional<scene::SoundNode::Settings> sound_settings = std::nullopt);
    explicit SoundPlayEvent(std::string_view sound_id, std::function<bool()> sound_stop_condition,
                            const sf::Vector2f& sound_position = sf::Vector2f(0, 0),
                            std::optional<scene::SoundNode::Settings> sound_settings = std::nullopt);
    ~SoundPlayEvent() override;

    void setSoundId(std::string_view sound_id);
    [[nodiscard]] std::string_view getSoundId() const;

    void setSoundPosition(const sf::Vector2f& sound_position);
    [[nodiscard]] const sf::Vector2f& getSoundPosition() const;

    void setSoundSettings(const scene::SoundNode::Settings& sound_settings);
    [[nodiscard]] const scene::SoundNode::Settings& getSoundSettings() const;

    void setAsLoop(bool loop);

    void setStopCondition(std::function<bool()> sound_stop_condition);
    [[nodiscard]] const std::function<bool()>& getSoundStopCondition();

    [[nodiscard]] bool hasSoundSettings() const;
    [[nodiscard]] bool isLoopSound() const;

  private:
    std::string_view m_sound_id;
    sf::Vector2f m_sound_position;
    std::optional<scene::SoundNode::Settings> m_sound_settings;
    bool m_sound_loop;
    std::function<bool()> m_sound_stop_condition;
  };

  class EGNIM_UTILITY_API SoundControlEvent : public Event
  {
    EGNIM_CLASS(SoundControlEvent, Event)

  public:
    explicit SoundControlEvent(sf::Sound::Status sound_status);
    ~SoundControlEvent() override;

    void setStatus(sf::Sound::Status sound_status);
    [[nodiscard]] sf::Sound::Status getStatus() const;

  private:
    sf::Sound::Status m_sound_status;
  };

} // namespace egnim::event

#endif //SOUND_EVENT_H
