#include "Request.hpp"

using namespace Messaging;

Request::Request(
  const std::string& id,
  const std::string& sender,
  const RequestType& requestType,
  const std::string& resource) :
  id(id),
  sender(sender),
  requestType(requestType),
  resource(resource) {
}

Request::Request(
  const std::string& id,
  const std::string& sender,
  const RequestType& requestType,
  const std::string& resource,
  std::unique_ptr<IEntity> content) :
  id(id),
  sender(sender),
  requestType(requestType),
  resource(resource),
  content(std::move(content)) {
}
