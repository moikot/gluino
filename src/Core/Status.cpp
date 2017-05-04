#include "Status.hpp"
#include "Memory.hpp"

using namespace Core;

Status Status::OK(StatusCode::OK, "OK");
Status Status::NotImplemented(StatusCode::NotImplemented, "Not implemented.");

Status::Status() : code(StatusCode::OK), message("OK") {
}

Status::Status(const StatusCode& code, const std::string& message) :
  code(code), message(message) {
}

Status::Status(const StatusCode& code, const std::string& message, Status innerResult) :
  code(code), message(message), innerStatus(std::make_unique<Status>(innerResult)) {
}

Status::Status(const Status& status) :
  code(status.code), message(status.message) {
  if (status.getInnerStatus()) {
    innerStatus = std::make_unique<Status>(*status.getInnerStatus());
  }
}

Status&
Status::operator = (const Status& status) {
  if (this != &status) {
    code = status.code;
    message = status.message;
    if (status.getInnerStatus()) {
      innerStatus = std::make_unique<Status>(*status.getInnerStatus());
    }
  }
  return *this;
}
