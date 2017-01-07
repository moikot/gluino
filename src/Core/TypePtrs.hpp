// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_TYPE_PTRS_HPP
#define CORE_TYPE_PTRS_HPP

#include <memory>

namespace Core {

#define TYPE_PTRS_ABSTRACT(Class) \
public: \
  typedef std::shared_ptr<Class> Shared; \
  typedef std::unique_ptr<Class> Unique; \

#define TYPE_PTRS(Class) \
  TYPE_PTRS_ABSTRACT(Class) \
  \
  template <typename... Args> \
  static Unique makeUnique(Args&&... args) { \
    return Unique(new Class(std::forward<Args>(args)...)); \
  } \
  \
  template <typename... Args> \
  static Shared makeShared(Args&&... args) { \
    return std::make_shared<Class>(std::forward<Args>(args)...); \
  } \

}

#endif /* end of include guard: CORE_TYPE_PTRS_HPP */
