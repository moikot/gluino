// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_I_LIST_HPP
#define CORE_I_LIST_HPP

#include "IEntity.hpp"
#include "StatusResult.hpp"

#include <functional>

namespace Core {

class IList : public IEntity {
  TYPE_PTRS_ABSTRACT(IList)
  public:
    virtual ~IList();

    typedef std::function<StatusResult::Unique
      (const IEntity& item)> ForEachFunction;

    virtual Core::StatusResult::Unique add(
      const IEntity& item) const = 0;
    virtual Core::StatusResult::Unique forEach(
      ForEachFunction func) const = 0;
};

}

#endif /* end of include guard: CORE_I_LIST_HPP */
