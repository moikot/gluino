// Copyright Sergey Anisimov 2016-2017

// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_ACTION_RESULT_HPP
#define CORE_ACTION_RESULT_HPP

#include "IEntity.hpp"
#include "StatusCode.hpp"

namespace Core {

class ActionResult : public IEntity {
TYPE_PTRS_ABSTRACT(ActionResult)
public:
  virtual StatusCode getStatusCode() const = 0;
};

}

#endif /* end of include guard: CORE_ACTION_RESULT_HPP */
