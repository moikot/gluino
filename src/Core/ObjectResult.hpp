// Copyright Sergey Anisimov 2016-2017

// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_OBJECT_RESULT_HPP
#define CORE_OBJECT_RESULT_HPP

#include "ActionResult.hpp"

namespace Core {

class ObjectResult : public ActionResult {
  TYPE_INFO(ObjectResult, ActionResult, "objectResult")

public:
  ObjectResult(StatusCode statusCode, IEntity::Unique entity) :
    statusCode(statusCode), entity(std::move(entity)) {}

  virtual StatusCode getStatusCode() const override {
    return statusCode;
  }

  const IEntity& getObject() const {
    return *entity;
  }

private:
  const StatusCode statusCode;
  const IEntity::Unique entity;
};

}

#endif /* end of include guard: CORE_OBJECT_RESULT_HPP */
