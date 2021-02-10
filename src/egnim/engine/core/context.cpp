/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/context.h>
/* -------------------------------------------------------------------------- */

namespace core {

Context::Context() :
  m_textures(make_unique_lazy<textures_holder>()),
  m_shaders(make_unique_lazy<shaders_holder>()),
  m_fonts(make_unique_lazy<fonts_holder>()),
  m_musics(make_unique_lazy<musics_holder>()),
  m_sound_buffers(make_unique_lazy<sound_buffer_holder>())
{

}

Context::~Context() = default;

Context::textures_holder& Context::getTextureHolder()
{
  return *m_textures;
}

Context::shaders_holder& Context::getShadersHolder()
{
  return *m_shaders;
}

Context::fonts_holder& Context::getFontsHolder()
{
  return *m_fonts;
}

Context::musics_holder& Context::getMusicsHolder()
{
  return *m_musics;
}

Context::sound_buffer_holder& Context::getSoundsHolder()
{
  return *m_sound_buffers;
}

const Context::textures_holder& Context::getTextureHolder() const
{
  return *m_textures;
}

const Context::shaders_holder& Context::getShadersHolder() const
{
  return *m_shaders;
}

const Context::fonts_holder& Context::getFontsHolder() const
{
  return *m_fonts;
}

const Context::musics_holder& Context::getMusicsHolder() const
{
  return *m_musics;
}

const Context::sound_buffer_holder& Context::getSoundBuffersHolder() const
{
  return *m_sound_buffers;
}

} // namespace core
