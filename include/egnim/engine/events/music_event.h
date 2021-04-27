#ifndef MUSIC_EVENT_H
#define MUSIC_EVENT_H

/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/events/event.h>
#include <egnim/engine/scene/music_node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events
{

  class EGNIM_UTILITY_API MusicPlayEvent : public Event
  {
    EGNIM_CLASS(MusicPlayEvent, Event)

  public:
    explicit MusicPlayEvent(std::string_view music_id, bool loop = false, std::optional<scene::MusicNode::Settings> music_settings = std::nullopt);
    ~MusicPlayEvent() override;

    void setMusicId(std::string_view music_id);
    [[nodiscard]] std::string_view getMusicId() const;

    void setMusicSettings(const scene::MusicNode::Settings& music_settings);
    [[nodiscard]] const scene::MusicNode::Settings& getMusicSettings() const;

    void setAsLoop(bool loop);

    [[nodiscard]] bool hasMusicSettings() const;
    [[nodiscard]] bool isLoopMusic() const;

  private:
    std::string_view m_music_id;
    std::optional<scene::MusicNode::Settings> m_music_settings;
    bool m_music_loop;
  };

  class EGNIM_UTILITY_API MusicControlEvent : public Event
  {
    EGNIM_CLASS(MusicControlEvent, Event)

  public:
    explicit MusicControlEvent(sf::Music::Status music_status);
    ~MusicControlEvent() override;

    void setStatus(sf::Music::Status music_status);
    [[nodiscard]] sf::Music::Status getStatus() const;

  private:
    sf::Music::Status m_music_status;
  };

} // namespace egnim::events

#endif //MUSIC_EVENT_H
