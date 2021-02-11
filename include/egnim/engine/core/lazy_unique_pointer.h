#ifndef LAZY_UNIQUE_POINTER_H
#define LAZY_UNIQUE_POINTER_H

/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <functional>
/* -------------------------------------------------------------------------- */

namespace core
{
  template<typename TYPE>
  class DefaultCreator
  {
  public:
    std::unique_ptr<TYPE> operator()() const;

    DefaultCreator() = default;
    DefaultCreator(DefaultCreator&&) noexcept = default;
    DefaultCreator& operator=(DefaultCreator&&) noexcept = default;
  };

  template<typename TYPE, typename CREATOR = DefaultCreator<TYPE>>
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

  private:
    explicit LazyUniquePointer(CREATOR&& creator);
    explicit LazyUniquePointer();

    TYPE* getter();
    const TYPE* getter() const;

  private:
    mutable std::unique_ptr<TYPE> m_object;
    mutable std::optional<CREATOR> m_creator;
  };

  /* ----------------------------- DefaultCreator<TYPE> ----------------------- */

  template<typename TYPE>
  std::unique_ptr<TYPE> DefaultCreator<TYPE>::operator()() const
  {
    return std::make_unique<TYPE>();
  }

  /* ------------------------------- make_unique_lazy ------------------------- */

  template<typename MAKER_TYPE>
  auto make_unique_lazy()
  {
    return LazyUniquePointer<MAKER_TYPE, DefaultCreator<MAKER_TYPE>>();
  }

  template<typename MAKER_TYPE, typename ...ARGS>
  auto make_unique_lazy(ARGS&& ...args)
  {
    auto creator = [&args...](){
      return std::make_unique<MAKER_TYPE>(std::forward<ARGS>(args)...);
    };

    return LazyUniquePointer<MAKER_TYPE, decltype(creator)>(std::move(creator));
  }

  template<typename MAKER_TYPE, typename CALLABLE, typename ...ARGS,
    typename = std::enable_if_t<std::is_invocable<CALLABLE, MAKER_TYPE&>::value>>
  auto make_unique_lazy(CALLABLE&& initializer, ARGS&& ...args)
  {
    auto creator = [&args..., &initializer](){
      auto object = std::make_unique<MAKER_TYPE>(std::forward<ARGS>(args)...);
      std::forward<CALLABLE>(initializer)(*object);
      return object;
    };

    return LazyUniquePointer<MAKER_TYPE, decltype(creator)>(std::move(creator));
  }

  /* ------------------------------ LazyPointer<TYPE> ------------------------- */

  template<typename TYPE, typename CREATOR>
  LazyUniquePointer<TYPE, CREATOR>::LazyUniquePointer(LazyUniquePointer&& other) noexcept
  {
    m_object = std::move(other.m_object);
    m_creator = std::move(other.m_creator);

    other.m_object.reset();
    other.m_creator.reset();
  }

  template<typename TYPE, typename CREATOR>
  LazyUniquePointer<TYPE, CREATOR>& LazyUniquePointer<TYPE, CREATOR>::operator=(LazyUniquePointer&& other) noexcept
  {
    m_object = std::move(other.m_object);
    m_creator = std::move(other.m_creator);

    other.m_object.reset();
    other.m_creator.reset();

    return *this;
  }

  template<typename TYPE, typename CREATOR>
  TYPE& LazyUniquePointer<TYPE, CREATOR>::operator*()
  {
    return *getter();
  }

  template<typename TYPE, typename CREATOR>
  const TYPE& LazyUniquePointer<TYPE, CREATOR>::operator*() const
  {
    return *getter();
  }

  template<typename TYPE, typename CREATOR>
  TYPE* LazyUniquePointer<TYPE, CREATOR>::operator->()
  {
    return getter();
  }

  template<typename TYPE, typename CREATOR>
  const TYPE* LazyUniquePointer<TYPE, CREATOR>::operator->() const
  {
    return getter();
  }

  template<typename TYPE, typename CREATOR>
  LazyUniquePointer<TYPE, CREATOR>::operator bool() const
  {
    return static_cast<bool>(getter());
  }

  template<typename TYPE, typename CREATOR>
  LazyUniquePointer<TYPE, CREATOR>::LazyUniquePointer(CREATOR&& creator) :
    m_creator(std::forward<CREATOR>(creator))
  {

  }

  template<typename TYPE, typename CREATOR>
  LazyUniquePointer<TYPE, CREATOR>::LazyUniquePointer() :
    m_creator(CREATOR{})
  {

  }

  template<typename TYPE, typename CREATOR>
  LazyUniquePointer<TYPE, CREATOR>::LazyUniquePointer(std::nullptr_t) :
    m_creator(std::nullopt)
  {

  }

  template<typename TYPE, typename CREATOR>
  TYPE* LazyUniquePointer<TYPE, CREATOR>::getter()
  {
    if(!m_object)
      m_object = m_creator ? (*m_creator)() : nullptr;

    return m_object.get();
  }

  template<typename TYPE, typename CREATOR>
  const TYPE* LazyUniquePointer<TYPE, CREATOR>::getter() const
  {
    if(!m_object)
      m_object = m_creator ? (*m_creator)() : nullptr;

    return m_object.get();
  }

} // namespace core

#endif //LAZY_UNIQUE_POINTER_H
