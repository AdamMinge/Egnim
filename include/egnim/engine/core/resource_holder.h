#ifndef RESOURCE_HOLDER_H
#define RESOURCE_HOLDER_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/InputStream.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <string_view>
#include <cassert>
#include <memory>
#include <map>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

  template<typename RESOURCE, typename IDENTIFIER>
  class ResourceHolderInterface
  {
  public:
    virtual ~ResourceHolderInterface() = default;

    [[nodiscard]] RESOURCE& get(IDENTIFIER id);
    [[nodiscard]] const RESOURCE& get(IDENTIFIER id) const;

    void remove(IDENTIFIER id);
    std::unique_ptr<RESOURCE> take(IDENTIFIER id);

    [[nodiscard]] bool contains(IDENTIFIER id) const;

  protected:
    explicit ResourceHolderInterface() = default;
    bool insertResource(IDENTIFIER id, std::unique_ptr<RESOURCE> resource);

  protected:
    std::map<IDENTIFIER, std::unique_ptr<RESOURCE>> m_resources;

  };

  template<typename RESOURCE, typename IDENTIFIER>
  class BaseResourceHolder : public ResourceHolderInterface<RESOURCE, IDENTIFIER>
  {
  public:
    explicit BaseResourceHolder() = default;
    ~BaseResourceHolder() override = default;

    bool loadFromFile(IDENTIFIER id, std::string_view filename);
    bool loadFromMemory(IDENTIFIER id, const void* data, size_t size_in_bytes);
    bool loadFromStream(IDENTIFIER id, sf::InputStream& stream);
  };

  template<typename IDENTIFIER>
  class BaseResourceHolder<sf::Texture, IDENTIFIER> : public ResourceHolderInterface<sf::Texture, IDENTIFIER>
  {
  public:
    explicit BaseResourceHolder() = default;
    ~BaseResourceHolder() override = default;

    bool loadFromFile(IDENTIFIER id, std::string_view texture_filename, const sf::IntRect& area = sf::IntRect());
    bool loadFromMemory(IDENTIFIER id, const void* data, size_t size_in_bytes, const sf::IntRect& area = sf::IntRect());
    bool loadFromStream(IDENTIFIER id, sf::InputStream& texture_stream, const sf::IntRect& area = sf::IntRect());
  };

  template<typename IDENTIFIER>
  class BaseResourceHolder<sf::Shader, IDENTIFIER>  : public ResourceHolderInterface<sf::Shader, IDENTIFIER>
  {
  public:
    explicit BaseResourceHolder() = default;
    ~BaseResourceHolder() override = default;

    bool loadFromFile(IDENTIFIER id, std::string_view shader_filename, sf::Shader::Type type);
    bool loadFromFile(IDENTIFIER id, std::string_view vertex_shader_filename, std::string_view fragment_shader_filename);
    bool loadFromFile(IDENTIFIER id, std::string_view vertex_shader_filename, std::string_view fragment_shader_filename,
                      std::string_view geometry_shader_filename);

    bool loadFromMemory(IDENTIFIER id, std::string_view shader, sf::Shader::Type type);
    bool loadFromMemory(IDENTIFIER id, std::string_view vertex_shader, std::string_view fragment_shader);
    bool loadFromMemory(IDENTIFIER id, std::string_view vertex_shader, std::string_view fragment_shader,
                        std::string_view geometry_shader);

    bool loadFromStream(IDENTIFIER id, sf::InputStream& shader_stream, sf::Shader::Type type);
    bool loadFromStream(IDENTIFIER id, sf::InputStream& vertex_shader_stream, sf::InputStream& fragment_shader_stream);
    bool loadFromStream(IDENTIFIER id, sf::InputStream& vertex_shader_stream, sf::InputStream& fragment_shader_stream,
                        sf::InputStream& geometry_shader_stream);
  };

  /* --------------------- ResourceHolder<RESOURCE,IDENTIFIER> ---------------- */

  template<typename RESOURCE, typename IDENTIFIER>
  RESOURCE& ResourceHolderInterface<RESOURCE, IDENTIFIER>::get(IDENTIFIER id)
  {
    assert(m_resources.contains(id));
    return *m_resources.at(id);
  }

  template<typename RESOURCE, typename IDENTIFIER>
  const RESOURCE& ResourceHolderInterface<RESOURCE, IDENTIFIER>::get(IDENTIFIER id) const
  {
    assert(m_resources.contains(id));
    return *m_resources.at(id);
  }

  template<typename RESOURCE, typename IDENTIFIER>
  void ResourceHolderInterface<RESOURCE, IDENTIFIER>::remove(IDENTIFIER id)
  {
    assert(m_resources.contains(id));
    m_resources.erase(id);
  }

  template<typename RESOURCE, typename IDENTIFIER>
  std::unique_ptr<RESOURCE> ResourceHolderInterface<RESOURCE, IDENTIFIER>::take(IDENTIFIER id)
  {
    if(!m_resources.contains(id))
      return nullptr;

    auto resource = std::move(m_resources[id]);
    m_resources.erase(id);
    return resource;
  }

  template<typename RESOURCE, typename IDENTIFIER>
  bool ResourceHolderInterface<RESOURCE, IDENTIFIER>::contains(IDENTIFIER id) const
  {
    return m_resources.contains(id);
  }

  template<typename RESOURCE, typename IDENTIFIER>
  bool ResourceHolderInterface<RESOURCE, IDENTIFIER>::insertResource(IDENTIFIER id, std::unique_ptr<RESOURCE> resource)
  {
    if(m_resources.contains(id))
      return false;

    m_resources.insert(std::make_pair(id, std::move(resource)));
    return true;
  }

  /* ------------------- BaseResourceHolder<RESOURCE,IDENTIFIER> -------------- */

  template<typename RESOURCE, typename IDENTIFIER>
  bool BaseResourceHolder<RESOURCE, IDENTIFIER>::loadFromFile(IDENTIFIER id, std::string_view filename)
  {
    auto resource = std::make_unique<RESOURCE>();
    if(!resource->loadFromFile(filename))
      return false;

    return insertResource(id, resource);
  }

  template<typename RESOURCE, typename IDENTIFIER>
  bool BaseResourceHolder<RESOURCE, IDENTIFIER>::loadFromMemory(IDENTIFIER id, const void* data, size_t size_in_bytes)
  {
    auto resource = std::make_unique<RESOURCE>();
    if(!resource->loadFromMemory(data, size_in_bytes))
      return false;

    return insertResource(id, resource);
  }

  template<typename RESOURCE, typename IDENTIFIER>
  bool BaseResourceHolder<RESOURCE, IDENTIFIER>::loadFromStream(IDENTIFIER id, sf::InputStream& stream)
  {
    auto resource = std::make_unique<RESOURCE>();
    if(!resource->loadFromStream(stream))
      return false;

    return insertResource(id, resource);
  }

  /* -------------------- ResourceHolder<sf::Texture,IDENTIFIER> -------------- */

  template<typename IDENTIFIER>
  bool BaseResourceHolder<sf::Texture, IDENTIFIER>::loadFromFile(IDENTIFIER id, std::string_view texture_filename,
                                                                 const sf::IntRect& area)
  {
    auto resource = std::make_unique<sf::Texture>();
    if(!resource->loadFromFile(std::string{texture_filename}, area))
      return false;

    return insertResource(id, resource);
  }

  template<typename IDENTIFIER>
  bool BaseResourceHolder<sf::Texture, IDENTIFIER>::loadFromMemory(IDENTIFIER id,
                                                                   const void* data, size_t size_in_bytes,
                                                                   const sf::IntRect& area)
  {
    auto resource = std::make_unique<sf::Texture>();
    if(!resource->loadFromMemory(data, size_in_bytes, area))
      return false;

    return insertResource(id, resource);
  }

  template<typename IDENTIFIER>
  bool BaseResourceHolder<sf::Texture, IDENTIFIER>::loadFromStream(IDENTIFIER id,
                                                                   sf::InputStream& texture_stream,
                                                                   const sf::IntRect& area)
  {
    auto resource = std::make_unique<sf::Texture>();
    if(!resource->loadFromStream(texture_stream, area))
      return false;

    return insertResource(id, resource);
  }

  /* -------------------- ResourceHolder<sf::Shader,IDENTIFIER> --------------- */

  template<typename IDENTIFIER>
  bool BaseResourceHolder<sf::Shader, IDENTIFIER>::loadFromFile(IDENTIFIER id, std::string_view shader_filename,
                                                                sf::Shader::Type type)
  {
    auto resource = std::make_unique<sf::Shader>();
    if(!resource->loadFromFile(std::string{shader_filename}, type))
      return false;

    return insertResource(id, resource);
  }

  template<typename IDENTIFIER>
  bool BaseResourceHolder<sf::Shader, IDENTIFIER>::loadFromFile(IDENTIFIER id, std::string_view vertex_shader_filename,
                                                                std::string_view fragment_shader_filename)
  {
    auto resource = std::make_unique<sf::Shader>();
    if(!resource->loadFromFile(std::string{vertex_shader_filename},
                               std::string{fragment_shader_filename}))
      return false;

    return insertResource(id, resource);
  }

  template<typename IDENTIFIER>
  bool BaseResourceHolder<sf::Shader, IDENTIFIER>::loadFromFile(IDENTIFIER id, std::string_view vertex_shader_filename,
                                                                std::string_view fragment_shader_filename,
                                                                std::string_view geometry_shader_filename)
  {
    auto resource = std::make_unique<sf::Shader>();
    if(!resource->loadFromFile(std::string{vertex_shader_filename},
                               std::string{geometry_shader_filename},
                               std::string{fragment_shader_filename}))
      return false;

    return insertResource(id, resource);
  }

  template<typename IDENTIFIER>
  bool BaseResourceHolder<sf::Shader, IDENTIFIER>::loadFromMemory(IDENTIFIER id, std::string_view shader,
                                                                  sf::Shader::Type type)
  {
    auto resource = std::make_unique<sf::Shader>();
    if(!resource->loadFromMemory(std::string{shader}, type))
      return false;

    return insertResource(id, resource);
  }

  template<typename IDENTIFIER>
  bool BaseResourceHolder<sf::Shader, IDENTIFIER>::loadFromMemory(IDENTIFIER id, std::string_view vertex_shader,
                                                                  std::string_view fragment_shader)
  {
    auto resource = std::make_unique<sf::Shader>();
    if(!resource->loadFromMemory(std::string{vertex_shader}, std::string{fragment_shader}))
      return false;

    return insertResource(id, resource);
  }

  template<typename IDENTIFIER>
  bool BaseResourceHolder<sf::Shader, IDENTIFIER>::loadFromMemory(IDENTIFIER id, std::string_view vertex_shader,
                                                                  std::string_view fragment_shader,
                                                                  std::string_view geometry_shader)
  {
    auto resource = std::make_unique<sf::Shader>();
    if(!resource->loadFromMemory(std::string{vertex_shader},
                                 std::string{fragment_shader},
                                 std::string{geometry_shader}))
      return false;

    return insertResource(id, resource);
  }

  template<typename IDENTIFIER>
  bool BaseResourceHolder<sf::Shader, IDENTIFIER>::loadFromStream(IDENTIFIER id, sf::InputStream& shader_stream,
                                                                  sf::Shader::Type type)
  {
    auto resource = std::make_unique<sf::Shader>();
    if(!resource->loadFromStream(shader_stream, type))
      return false;

    return insertResource(id, resource);
  }

  template<typename IDENTIFIER>
  bool BaseResourceHolder<sf::Shader, IDENTIFIER>::loadFromStream(IDENTIFIER id, sf::InputStream& vertex_shader_stream,
                                                                  sf::InputStream& fragment_shader_stream)
  {
    auto resource = std::make_unique<sf::Shader>();
    if(!resource->loadFromStream(vertex_shader_stream, fragment_shader_stream))
      return false;

    return insertResource(id, resource);
  }

  template<typename IDENTIFIER>
  bool BaseResourceHolder<sf::Shader, IDENTIFIER>::loadFromStream(IDENTIFIER id,
                                                                  sf::InputStream& vertex_shader_stream,
                                                                  sf::InputStream& fragment_shader_stream,
                                                                  sf::InputStream& geometry_shader_stream)
  {
    auto resource = std::make_unique<sf::Shader>();
    if(!resource->loadFromStream(vertex_shader_stream, geometry_shader_stream, fragment_shader_stream))
      return false;

    return insertResource(id, resource);
  }

} // namespace egnim::core

#endif //RESOURCE_HOLDER_H
