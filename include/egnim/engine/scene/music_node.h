#ifndef MUSIC_NODE_H
#define MUSIC_NODE_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Audio/Music.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/scene/node.h>
#include <egnim/engine/core/resource_holder.h>
#include <egnim/engine/scene/node_factory.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{

  class EGNIM_UTILITY_API MusicNode : public Node, public RegisteredInNodeFactory<MusicNode>
  {
    EGNIM_CLASS(MusicNode, Node)

  public:
    struct Settings
    {
      float attenuation = 1.f;
      float min_distance = 1.f;
      float pitch = 1.f;
      float volume = 100.f;
    };

  public:
    explicit MusicNode();
    ~MusicNode() override;

    void setMusicsHolder(core::BaseResourceHolder<sf::Music, std::string_view>* musics_holder);
    core::BaseResourceHolder<sf::Music, std::string_view>* getMusicsHolder() const;

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

    void accept(SceneVisitor& visitor) override;

  private:
    core::BaseResourceHolder<sf::Music, std::string_view>* m_musics_holder;
    Settings m_default_settings;
    sf::Music* m_current_music;
  };

} // namespace egnim::scene

#endif //MUSIC_NODE_H
