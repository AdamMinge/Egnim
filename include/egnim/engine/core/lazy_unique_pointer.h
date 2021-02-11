#ifndef LAZY_UNIQUE_POINTER_H
#define LAZY_UNIQUE_POINTER_H

/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <functional>
#include <type_traits>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

  template<typename TYPE>
  class LazyUniquePointer
  {
    template<typename MAKER_TYPE>
    friend auto make_unique_lazy();

    template<typename MAKER_TYPE, typename ...ARGS>
    friend auto make_unique_lazy(ARGS&& ...args);

    template<typename MAKER_TYPE, typename CALLABLE, typename ...ARGS, typename>
    friend auto make_unique_lazy(CALLABLE&& initializer, ARGS&& ...args);

  public:
    explicit LazyUniquePointer(std::nullptr_t);
    ~LazyUniquePointer() = default;

    LazyUniquePointer(LazyUniquePointer&& other) noexcept;
    LazyUniquePointer& operator=(LazyUniquePointer&& other) noexcept;

    LazyUniquePointer(const LazyUniquePointer&) = delete;
    LazyUniquePointer& operator=(const LazyUniquePointer&) = delete;

    TYPE& operator*();
    const TYPE& operator*() const;

    TYPE* operator->();
    const TYPE* operator->() const;

    explicit operator bool() const;

    void init() const;

  private:
    explicit LazyUniquePointer(std::function<std::unique_ptr<TYPE>()>&& creator);

    TYPE* getter();
    const TYPE* getter() const;

  private:
    mutable std::unique_ptr<TYPE> m_object;
    mutable std::optional<std::function<std::unique_ptr<TYPE>()>> m_creator;
  };

  /* ------------------------------- make_unique_lazy ------------------------- */

  template<typename MAKER_TYPE>
  auto make_unique_lazy()
  {
    auto creator = std::function<std::unique_ptr<MAKER_TYPE>()>([](){
      return std::make_unique<MAKER_TYPE>();
    });

    return LazyUniquePointer<MAKER_TYPE>(std::move(creator));
  }

  template<typename MAKER_TYPE, typename ...ARGS>
  auto make_unique_lazy(ARGS&& ...args)
  {
    auto creator = std::function<std::unique_ptr<MAKER_TYPE>()>([&args...](){
      return std::make_unique<MAKER_TYPE>(std::forward<ARGS>(args)...);
    });

    return LazyUniquePointer<MAKER_TYPE>(std::move(creator));
  }

  template<typename MAKER_TYPE, typename CALLABLE, typename ...ARGS,
    typename = std::enable_if_t<std::is_invocable<CALLABLE, MAKER_TYPE&>::value>>
  auto make_unique_lazy(CALLABLE&& initializer, ARGS&& ...args)
  {
    auto creator = std::function<std::unique_ptr<MAKER_TYPE>()>([&args..., &initializer](){
      auto object = std::make_unique<MAKER_TYPE>(std::forward<ARGS>(args)...);

      static_assert(std::is_same_v<bool, decltype(std::declval<CALLABLE>())> ||
                    std::is_same_v<void, decltype(std::declval<CALLABLE>())>,
                    "Callable initializer returning type must be one of (bool, void)");

      if constexpr (std::is_same_v<bool, decltype(std::declval<CALLABLE>())>)
      {
        if(!std::forward<CALLABLE>(initializer)(*object))
          return nullptr;
      }
      else
      {
        std::forward<CALLABLE>(initializer)(*object);
      }

      return object;
    });

    return LazyUniquePointer<MAKER_TYPE>(std::move(creator));
  }

  /* ------------------------------ LazyPointer<TYPE> ------------------------- */

  template<typename TYPE>
  LazyUniquePointer<TYPE>::LazyUniquePointer(LazyUniquePointer<TYPE>&& other) noexcept
  {
    m_object = std::move(other.m_object);
    m_creator = std::move(other.m_creator);

    other.m_object.reset();
    other.m_creator.reset();
  }

  template<typename TYPE>
  LazyUniquePointer<TYPE>& LazyUniquePointer<TYPE>::operator=(LazyUniquePointer<TYPE>&& other) noexcept
  {
    m_object = std::move(other.m_object);
    m_creator = std::move(other.m_creator);

    other.m_object.reset();
    other.m_creator.reset();

    return *this;
  }

  template<typename TYPE>
  TYPE& LazyUniquePointer<TYPE>::operator*()
  {
    return *getter();
  }

  template<typename TYPE>
  const TYPE& LazyUniquePointer<TYPE>::operator*() const
  {
    return *getter();
  }

  template<typename TYPE>
  TYPE* LazyUniquePointer<TYPE>::operator->()
  {
    return getter();
  }

  template<typename TYPE>
  const TYPE* LazyUniquePointer<TYPE>::operator->() const
  {
    return getter();
  }

  template<typename TYPE>
  LazyUniquePointer<TYPE>::operator bool() const
  {
    return static_cast<bool>(getter());
  }

  template<typename TYPE>
  void LazyUniquePointer<TYPE>::init() const
  {
    if(!m_object)
    {
      m_object = m_creator ? (*m_creator)() : nullptr;
      m_creator.reset();
    }
  }

  template<typename TYPE>
  LazyUniquePointer<TYPE>::LazyUniquePointer(std::function<std::unique_ptr<TYPE>()>&& creator) :
    m_creator(std::move(creator))
  {

  }

  template<typename TYPE>
  LazyUniquePointer<TYPE>::LazyUniquePointer(std::nullptr_t) :
    m_creator(std::nullopt)
  {

  }

  template<typename TYPE>
  TYPE* LazyUniquePointer<TYPE>::getter()
  {
    init();
    return m_object.get();
  }

  template<typename TYPE>
  const TYPE* LazyUniquePointer<TYPE>::getter() const
  {
    init();
    return m_object.get();
  }

} // namespace egnim::core

#endif //LAZY_UNIQUE_POINTER_H
