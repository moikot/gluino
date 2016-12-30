// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_TYPE_INFO_HPP
#define CORE_TYPE_INFO_HPP

#include "TypePtrs.hpp"

#include <string>

namespace Core {

#define TYPE_INFO(Class, SuperClass, ClassTypeId) \
public: \
  TYPE_PTRS(Class) \
  \
  static constexpr const char* TypeId = ClassTypeId; \
  \
  virtual const char* getTypeId() const override { return TypeId; } \
  \
  static  bool        isType(const std::string& typeId) { \
    return (typeId == ClassTypeId || SuperClass::isType(typeId)); \
  } \
  \
  static Class* cast(Core::IEntity* entity) { \
    if (Class::isType(entity->getTypeId())) \
      return static_cast<Class*>(entity); \
    return nullptr; \
  } \
  \
  static const Class* cast(const Core::IEntity* entity) { \
    if (Class::isType(entity->getTypeId())) \
      return static_cast<const Class*>(entity); \
    return nullptr; \
  } \

}

#endif /* end of include guard: CORE_TYPE_INFO_HPP */
