// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_I_ENTITY_HPP
#define CORE_I_ENTITY_HPP

#include "Core/TypeInfo.hpp"

namespace Core {

/**
  The base class for all the domain objects.
*/
class IEntity {
public:
  virtual ~IEntity() = default;

  /**
    Returns the type of the instance.

    @return The type of the instance.
  */
  virtual const std::string& getTypeId() const = 0;

  /**
    Checks if this class is a class of a particular type.

    @param typeId The class type.
    @return True if this class is the class of a particular type; false otherwise.
  */
  virtual bool isType(const std::string&) const {
    return false; // Returns always false for the abstract IEntity
  }
};

}

#endif /* end of include guard: CORE_I_ENTITY_HPP */
