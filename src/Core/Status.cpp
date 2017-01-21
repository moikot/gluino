#include "Status.hpp"

using namespace Core;

Status Status::OK(StatusCode::OK, "OK");
Status Status::NotImplemented(StatusCode::NotImplemented, "Not implemented.");

Status::Status(const StatusCode& statusCode, const std::string& message) :
  statusCode(statusCode), message(message) {
}

Status::Status(const StatusCode& statusCode, const std::string& message,
             Status innerResult) :
  statusCode(statusCode), message(message), innerStatus(makeUnique(innerResult)) {
}

Status::Status(const Status& status) : 
  statusCode(status.statusCode), message(status.message) {
  if (status.getInnerStatus()) {
    innerStatus = Status::makeUnique(*status.getInnerStatus());
  }
}

Status& 
Status::operator=(const Status& status) {
  if (this != &status) {
    statusCode = status.statusCode;
    message = status.message;
    if (status.getInnerStatus()) {
      innerStatus = Status::makeUnique(*status.getInnerStatus());
    }
  }
  return *this;
}