#ifndef CONTEXT_H
#define CONTEXT_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <string_view>
#include <memory>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/core/resource_holder.h>
#include <egnim/engine/core/lazy_unique_pointer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::event
{
  class EventDispatcher;
}

namespace egnim::core
{

  class EGNIM_UTILITY_API Context
  {
  public:
    using textures_holder = BaseResourceHolder<sf::Texture, std::string_view>;
    using shaders_holder = BaseResourceHolder<sf::Shader, std::string_view>;
    using fonts_holder = BaseResourceHolder<sf::Font, std::string_view>;
    using musics_holder = BaseResourceHolder<sf::Music, std::string_view>;
    using sound_buffer_holder = BaseResourceHolder<sf::SoundBuffer, std::string_view>;

  public:
    Context();
    ~Context();

    [[nodiscard]] textures_holder& getTextureHolder();
    [[nodiscard]] shaders_holder& getShadersHolder();
    [[nodiscard]] fonts_holder& getFontsHolder();
    [[nodiscard]] musics_holder& getMusicsHolder();
    [[nodiscard]] sound_buffer_holder& getSoundsHolder();
    [[nodiscard]] sf::RenderWindow& getRenderWindow();
    [[nodiscard]] event::EventDispatcher& getEventDispatcher();

    [[nodiscard]] const textures_holder& getTextureHolder() const;
    [[nodiscard]] const shaders_holder& getShadersHolder() const;
    [[nodiscard]] const fonts_holder& getFontsHolder() const;
    [[nodiscard]] const musics_holder& getMusicsHolder() const;
    [[nodiscard]] const sound_buffer_holder& getSoundBuffersHolder() const;
    [[nodiscard]] const sf::RenderWindow& getRenderWindow() const;
    [[nodiscard]] const event::EventDispatcher& getEventDispatcher() const;


  private:
    LazyUniquePointer<textures_holder> m_textures;
    LazyUniquePointer<shaders_holder> m_shaders;
    LazyUniquePointer<fonts_holder> m_fonts;
    LazyUniquePointer<musics_holder> m_musics;
    LazyUniquePointer<sound_buffer_holder> m_sound_buffers;
    LazyUniquePointer<sf::RenderWindow> m_render_window;
    LazyUniquePointer<event::EventDispatcher> m_event_dispatcher;
  };

} // namespace egnim::core

#endif //CONTEXT_H
