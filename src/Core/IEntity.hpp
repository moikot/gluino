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

  /**
    Returns the type of the instance.

    @return The type of the instance.
  */
  virtual const char* getTypeId() const = 0;

  /**
    Checks if this class is a class of a particular type.

    @param typeId The class type.
    @return True if this class is the class of a particular type; false otherwise.
  */
  static bool isType(const std::string& typeId) {
    return false; // Returns allways false for IEntity
  }
};

}

#endif /* end of include guard: CORE_I_ENTITY_HPP */
