#ifndef LAZY_POINTER_H
#define LAZY_POINTER_H

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
  };

  template<typename TYPE, typename CREATOR>
  class LazyUniquePointer
  {
    template<typename MAKER_TYPE>
    friend auto make_lazy();

    template<typename MAKER_TYPE, typename ...ARGS>
    friend auto make_lazy(ARGS&& ...args);

    template<typename MAKER_TYPE, typename CALLABLE, typename ...ARGS, typename>
    friend auto make_lazy(CALLABLE&& initializer, ARGS&& ...args);

  public:
    ~LazyUniquePointer() = default;

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
    const CREATOR m_creator;
  };

  /* ----------------------------- DefaultCreator<TYPE> ----------------------- */

  template<typename TYPE>
  std::unique_ptr<TYPE> DefaultCreator<TYPE>::operator()() const
  {
    return std::make_unique<TYPE>();
  }

  /* -------------------------------- MakeLazy<TYPE> -------------------------- */

  template<typename MAKER_TYPE>
  auto make_lazy()
  {
    return LazyUniquePointer<MAKER_TYPE, DefaultCreator<MAKER_TYPE>>();
  }

  template<typename MAKER_TYPE, typename ...ARGS>
  auto make_lazy(ARGS&& ...args)
  {
    auto creator = [args...](){
      return std::make_unique<MAKER_TYPE>(args...);
    };

    return LazyUniquePointer<MAKER_TYPE, decltype(creator)>(std::move(creator));
  }

  template<typename MAKER_TYPE, typename CALLABLE, typename ...ARGS,
    typename = std::enable_if_t<std::is_invocable<CALLABLE, MAKER_TYPE&>::value>>
  auto make_lazy(CALLABLE&& initializer, ARGS&& ...args)
  {
    auto creator = [args..., initializer](){
      auto object = std::make_unique<MAKER_TYPE>(args...);
      initializer(*object);
      return object;
    };

    return LazyUniquePointer<MAKER_TYPE, decltype(creator)>(std::move(creator));
  }

  /* ------------------------------ LazyPointer<TYPE> ------------------------- */

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
  TYPE* LazyUniquePointer<TYPE, CREATOR>::getter()
  {
    if(!m_object)
      m_object = m_creator();

    return m_object.get();
  }

  template<typename TYPE, typename CREATOR>
  const TYPE* LazyUniquePointer<TYPE, CREATOR>::getter() const
  {
    if(!m_object)
      m_object = m_creator();

    return m_object.get();
  }

} // namespace core

#endif //LAZY_POINTER_H
