// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_I_ENTITY_HPP
#define CORE_I_ENTITY_HPP

#include "Core/TypeInfo.hpp"

namespace Core {

class IEntity {
TYPE_PTRS_ABSTRACT(IEntity)
public:
  virtual ~IEntity();
  virtual const char* getTypeId() const = 0;

  static bool isType(const std::string& typeId) {
    return false;
  }
};

}

#endif /* end of include guard: CORE_I_ENTITY_HPP */
