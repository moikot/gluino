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
    static Status OK;
    static Status NotImplemented;

    Status(const StatusCode& statusCode, const std::string& message);
    Status(const StatusCode& statusCode, const std::string& message, Status innerStatus);

    Status(Status && op) noexcept;
    Status& operator=(Status && op) noexcept;

    Status(const Status& op);
    Status& operator=(const Status& op);

    bool isOk() const {
      return getStatusCode() == StatusCode::OK;
    }

    virtual StatusCode getStatusCode() const {
      return statusCode;
    }

    std::string getMessage() const {
      return message;
    }

    const Status* getInnerStatus() const {
      return innerStatus.get();
    }

  private:
    StatusCode		  statusCode;
    std::string		  message;
    Status::Unique	innerStatus;
};

}

#endif /* end of include guard: CORE_STATUS_RESULT_HPP */
