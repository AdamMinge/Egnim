/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/context.h>
/* -------------------------------------------------------------------------- */

namespace core {

Context::Context() :
  m_textures(nullptr),
  m_shaders(nullptr),
  m_fonts(nullptr),
  m_musics(nullptr),
  m_sound_buffers(nullptr)
{

}

Context::~Context() = default;

Context::textures_holder& Context::getTextureHolder()
{
  return *getter(m_textures);
}

Context::shaders_holder& Context::getShadersHolder()
{
  return *getter(m_shaders);
}

Context::fonts_holder& Context::getFontsHolder()
{
  return *getter(m_fonts);
}

Context::musics_holder& Context::getMusicsHolder()
{
  return *getter(m_musics);
}

Context::sound_buffer_holder& Context::getSoundsHolder()
{
  return *getter(m_sound_buffers);
}

const Context::textures_holder& Context::getTextureHolder() const
{
  return *getter(m_textures);
}

const Context::shaders_holder& Context::getShadersHolder() const
{
  return *getter(m_shaders);
}

const Context::fonts_holder& Context::getFontsHolder() const
{
  return *getter(m_fonts);
}

const Context::musics_holder& Context::getMusicsHolder() const
{
  return *getter(m_musics);
}

const Context::sound_buffer_holder& Context::getSoundBuffersHolder() const
{
  return *getter(m_sound_buffers);
}

} // namespace core
