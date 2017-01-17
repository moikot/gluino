// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_TYPE_INFO_HPP
#define CORE_TYPE_INFO_HPP

#include "TypePtrs.hpp"

#include <string>

namespace Core {

#define TYPE_INFO(Class, SuperClass, ClassTypeId) \
public: \
  TYPE_PTRS(Class) \
  \
  static const std::string& TypeId() { \
    static std::string typeId(ClassTypeId); \
    return typeId; \
  } \
  \
  virtual const std::string& getTypeId() const override { return TypeId(); } \
  \
  virtual bool isType(const std::string& typeId) const override { \
    return (typeId == ClassTypeId || SuperClass::isType(typeId)); \
  } \
  \
  static Class* cast(Core::IEntity* entity) { \
    if (entity->isType(Class::TypeId())) \
      return static_cast<Class*>(entity); \
    return nullptr; \
  } \
  \
  static const Class* cast(const Core::IEntity* entity) { \
    if (entity->isType(Class::TypeId())) \
      return static_cast<const Class*>(entity); \
    return nullptr; \
  } \

}

#endif /* end of include guard: CORE_TYPE_INFO_HPP */
