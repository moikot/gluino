// Copyright Sergey Anisimov 2016-2017

// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_ACTION_RESULT_HPP
#define CORE_ACTION_RESULT_HPP

#include "IEntity.hpp"
#include "StatusCode.hpp"

namespace Core {

class ActionResult : public IEntity {
  TYPE_PTRS_ABSTRACT(ActionResult)

  public:
    virtual StatusCode getStatusCode() const {
      return statusCode;
    }

  protected:
    ActionResult(StatusCode statusCode);

  private:
    const StatusCode statusCode;
};

}

#endif /* end of include guard: CORE_ACTION_RESULT_HPP */
