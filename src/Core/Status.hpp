// Copyright Sergey Anisimov 2016-2017

// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_STATUS_HPP
#define CORE_STATUS_HPP

#include "IEntity.hpp"
#include "StatusCode.hpp"

#include <memory>

namespace Core {

class Status : public IEntity {
  TYPE_INFO(Status, IEntity, "status")
  public:
    static Status OK;
    static Status NotImplemented;

    Status();
    Status(const StatusCode& statusCode, const std::string& message);
    Status(const StatusCode& statusCode, const std::string& message, const Status& innerStatus);

    Status(const Status& op);
    Status& operator=(const Status& op);

    Status(Status && op) = default;
    Status& operator=(Status && op) = default;

    bool isOk() const {
      return getCode() == StatusCode::OK;
    }

    virtual StatusCode getCode() const {
      return code;
    }

    std::string getMessage() const {
      return message;
    }

    const Status* getInnerStatus() const {
      return innerStatus.get();
    }

  private:
    StatusCode      code;
    std::string     message;
    std::unique_ptr<Status>	innerStatus;
};

}

#endif /* end of include guard: CORE_STATUS_HPP */
