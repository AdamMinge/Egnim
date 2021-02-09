#ifndef MUSIC_NODE_H
#define MUSIC_NODE_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Audio/Music.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/scene_node.h>
#include <egnim/engine/core/resource_holder.h>
/* -------------------------------------------------------------------------- */

namespace core
{

  class MusicNode : public SceneNode
  {
  public:
    struct Settings
    {
      float attenuation = 1.f;
      float min_distance = 1.f;
      float pitch = 1.f;
      float volume = 100.f;
    };

  public:
    explicit MusicNode(BaseResourceHolder<sf::Music, std::string_view>& musics_holder);
    ~MusicNode() override;

    void setDefaultSettings(const Settings& settings);
    const Settings& getDefaultSettings() const;

    bool play();
    bool play(std::string_view id, bool loop = false);
    bool play(std::string_view id, const Settings& settings, bool loop = false);

    void stop();
    void pause();

    bool isPlaying();
    bool isPaused();
    bool isStopped();

  private:
    BaseResourceHolder<sf::Music, std::string_view>& m_musics_holder;
    Settings m_default_settings;
    sf::Music* m_current_music;
  };

}

#endif //MUSIC_NODE_H
