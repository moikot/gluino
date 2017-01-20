#include "Status.hpp"

using namespace Core;

Status::Unique
Status::OK() {
  return Status::makeUnique(StatusCode::OK, "OK");
}

Status::Unique
Status::NotImplemented() {
  return Status::makeUnique(StatusCode::NotImplemented, "Not implemented.");
}

Status::Status(const StatusCode& statusCode, const std::string& message) :
  statusCode(statusCode), message(message) {
}

Status::Status(const StatusCode& statusCode, const std::string& message,
             Status::Unique innerResult) :
  statusCode(statusCode), message(message), innerResult(std::move(innerResult)) {
}
