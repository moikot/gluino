#include "Request.hpp"

using namespace Messaging;

Request::Request(
  std::string id,
  std::string sender,
  RequestType requestType,
  std::string resource) :
  id(id),
  sender(sender),
  requestType(requestType),
  resource(resource) {
}

Request::Request(
  std::string id,
  std::string sender,
  RequestType requestType,
  std::string resource,
  std::unique_ptr<IEntity> content) :
  id(id),
  sender(sender),
  requestType(requestType),
  resource(resource),
  content(std::move(content)) {
}
