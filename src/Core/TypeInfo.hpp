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

}

#endif /* end of include guard: CORE_TYPE_INFO_HPP */
