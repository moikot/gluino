// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_CASTING_HPP
#define CORE_CASTING_HPP

#include <memory>
#include <type_traits>

// MSVS defines this already.
// http://stackoverflow.com/questions/14131454/visual-studio-2012-cplusplus-and-c-11
#if defined(_MSC_VER) && _MSC_VER < 1800 || !defined(_MSC_VER) && __cplusplus <= 201103L
namespace std {
  // C++14 backfill from http://herbsutter.com/gotw/_102/
  template<typename T, typename ...Args>
  inline std::unique_ptr<T> make_unique(Args&& ...args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }
}
#endif

namespace Core {

template<class Derived, class Base>
Derived
cast(Base base) {
  if (base != nullptr) {
    if(std::is_convertible<typename std::remove_pointer<Base>::type,
       typename std::remove_pointer<Derived>::type>::value) {
      return reinterpret_cast<Derived>(base);
    }
    if (base->isType(std::remove_pointer<Derived>::type::TypeId())) {
      return reinterpret_cast<Derived>(base);
    }
  }
  return nullptr;
}

template<class Derived, class Base>
std::unique_ptr<Derived>
castToUnique(std::unique_ptr<Base>&& base)
{
  if (auto result = cast<Derived*>(base.get())){
    base.release();
    return std::unique_ptr<Derived>(result);
  }
  return std::unique_ptr<Derived>(nullptr);
}

template<class Derived, class Base>
std::shared_ptr<Derived>
castToShared(std::unique_ptr<Base>&& base)
{
   if (auto result = cast<Derived*>(base.get())){
        base.release();
        return std::shared_ptr<Derived>(result);
    }
    return std::shared_ptr<Derived>();
}

template<class Derived, class Base>
std::shared_ptr<Derived>
castToShared(const std::shared_ptr<Base>& base) noexcept
{
    if (auto ptr = cast<Derived*>(base.get())) {
        return std::shared_ptr<Derived>(base, ptr);
    } else {
        return std::shared_ptr<Derived>();
    }
}

}

#endif /* end of include guard: CORE_CASTING_HPP */
