#include "Status.hpp"
#include "Memory.hpp"

using namespace Core;

Status Status::OK(StatusCode::OK, "OK");
Status Status::NotImplemented(StatusCode::NotImplemented, "Not implemented.");

Status::Status(const StatusCode& statusCode, const std::string& message) :
  statusCode(statusCode), message(message) {
}

Status::Status(const StatusCode& statusCode, const std::string& message,
             Status innerResult) :
  statusCode(statusCode), message(message), innerStatus(std::make_unique<Status>(innerResult)) {
}

Status::Status(Status && op) = default;

Status& Status::operator = (Status && op) = default;

Status::Status(const Status& status) :
  statusCode(status.statusCode), message(status.message) {
  if (status.getInnerStatus()) {
    innerStatus = std::make_unique<Status>(*status.getInnerStatus());
  }
}

Status&
Status::operator = (const Status& status) {
  if (this != &status) {
    statusCode = status.statusCode;
    message = status.message;
    if (status.getInnerStatus()) {
      innerStatus = std::make_unique<Status>(*status.getInnerStatus());
    }
  }
  return *this;
}
