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
    template<typename RESOURCE_HOLDER>
    RESOURCE_HOLDER& getter(RESOURCE_HOLDER& holder) const;

  private:
    mutable std::unique_ptr<textures_holder> m_textures;
    mutable std::unique_ptr<shaders_holder> m_shaders;
    mutable std::unique_ptr<fonts_holder> m_fonts;
    mutable std::unique_ptr<musics_holder> m_musics;
    mutable std::unique_ptr<sound_buffer_holder> m_sound_buffers;
  };

  /* ----------------------------------- Context ------------------------------ */

  template<typename RESOURCE_HOLDER>
  RESOURCE_HOLDER& Context::getter(RESOURCE_HOLDER& holder) const
  {
    if(holder)
      holder = std::make_unique<typename std::remove_cvref_t<decltype(holder)>::element_type>();
    return holder;
  }

} // namespace core

#endif //CONTEXT_H
