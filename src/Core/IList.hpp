// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_I_LIST_HPP
#define CORE_I_LIST_HPP

#include "IEntity.hpp"
#include "Status.hpp"

#include <functional>

namespace Core {

/**
  The base class for all the collections of domain objects.
*/
class IList : public IEntity {
  public:
    typedef std::function<Status(const IEntity& item)> ForEachFunction;

    /**
      Add a new instance to the collection.

      @param item The domain object instance to add.
      @return The result of the operation.
    */
    virtual Core::Status add(const IEntity& item) const = 0;

    /**
      Iterates through all the objects in the collection.

      @param func The call back function called for each object in the collection.
      @return The result of the operation.
    */
    virtual Core::Status forEach(ForEachFunction func) const = 0;
};

}

#endif /* end of include guard: CORE_I_LIST_HPP */
