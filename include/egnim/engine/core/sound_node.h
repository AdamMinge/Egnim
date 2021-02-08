#ifndef SOUND_NODE_H
#define SOUND_NODE_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio/Sound.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <string_view>
#include <functional>
#include <list>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/scene_node.h>
#include <egnim/engine/core/context.h>
/* -------------------------------------------------------------------------- */

namespace core
{

  class SoundNode : public SceneNode
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
    explicit SoundNode(Context::sound_buffer_holder& sound_buffers);
    ~SoundNode() override;

    void setDefaultSettings(const Settings& settings);
    const Settings& getDefaultSettings() const;

    bool play(std::string_view id, sf::Vector2f position = sf::Vector2f(0.f, 0.f));
    bool play(std::string_view id, const Settings& settings, sf::Vector2f position = sf::Vector2f(0.f, 0.f));

    bool playLoop(std::string_view id, const std::function<bool()>& stop_condition,
                   sf::Vector2f position = sf::Vector2f(0.f, 0.f));
    bool playLoop(std::string_view id, const std::function<bool()>& stop_condition,
                   const Settings& settings, sf::Vector2f position = sf::Vector2f(0.f, 0.f));

    void stopAllSounds();
    void pauseAllSounds();
    void startAllSounds();

  protected:
    void updateCurrent(CommandQueue& command_queue, sf::Time dt) override;

  private:
    void checkStopConditions();
    void removeStoppedSounds();
    void setAllSounds(sf::Sound::Status status);

  private:
    Context::sound_buffer_holder& m_sound_buffers;
    std::list<std::pair<sf::Sound, std::function<bool()>>> m_sounds;
    Settings m_default_settings;
  };

}

#endif //SOUND_NODE_H
