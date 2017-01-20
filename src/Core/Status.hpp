// Copyright Sergey Anisimov 2016-2017

// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_STATUS_RESULT_HPP
#define CORE_STATUS_RESULT_HPP

#include "IEntity.hpp"
#include "StatusCode.hpp"

namespace Core {

class Status : public IEntity {
TYPE_INFO(Status, IEntity, "status")

public:
  static Status::Unique OK();
  static Status::Unique NotImplemented();

  Status(const StatusCode& statusCode,
               const std::string& message);

  Status(const StatusCode& statusCode,
               const std::string& message,
               Status::Unique innerResult);

  bool isOk() const {
    return getStatusCode() == StatusCode::OK;
  }

  virtual StatusCode getStatusCode() const {
    return statusCode;
  }

  std::string getMessage() const {
    return message;
  }

  const Status* getInnerReuslt() const {
    return innerResult.get();
  }

private:
  const StatusCode            statusCode;
  const std::string           message;
  const Status::Unique  innerResult;
};

}

#endif /* end of include guard: CORE_STATUS_RESULT_HPP */
