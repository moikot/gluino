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

class StatusResult : public IEntity {
TYPE_INFO(StatusResult, IEntity, "statusResult")

public:
  static StatusResult::Unique OK();
  static StatusResult::Unique NotImplemented();

  StatusResult(const StatusCode& statusCode,
               const std::string& message);

  StatusResult(const StatusCode& statusCode,
               const std::string& message,
               StatusResult::Unique innerResult);

  bool isOk() const {
    return getStatusCode() == StatusCode::OK;
  }

  virtual StatusCode getStatusCode() const {
    return statusCode;
  }

  std::string getMessage() const {
    return message;
  }

  const StatusResult* getInnerReuslt() const {
    return innerResult.get();
  }

private:
  const StatusCode            statusCode;
  const std::string           message;
  const StatusResult::Unique  innerResult;
};

}

#endif /* end of include guard: CORE_STATUS_RESULT_HPP */
