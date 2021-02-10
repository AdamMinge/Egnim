#ifndef CONTEXT_H
#define CONTEXT_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <string_view>
#include <memory>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/core/resource_holder.h>
#include <egnim/engine/core/lazy_unique_pointer.h>
/* -------------------------------------------------------------------------- */

namespace core
{

  class Context
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

    [[nodiscard]] const textures_holder& getTextureHolder() const;
    [[nodiscard]] const shaders_holder& getShadersHolder() const;
    [[nodiscard]] const fonts_holder& getFontsHolder() const;
    [[nodiscard]] const musics_holder& getMusicsHolder() const;
    [[nodiscard]] const sound_buffer_holder& getSoundBuffersHolder() const;

  private:
    LazyUniquePointer<textures_holder> m_textures;
    LazyUniquePointer<shaders_holder> m_shaders;
    LazyUniquePointer<fonts_holder> m_fonts;
    LazyUniquePointer<musics_holder> m_musics;
    LazyUniquePointer<sound_buffer_holder> m_sound_buffers;
  };

} // namespace core

#endif //CONTEXT_H
