#include "Request.hpp"

using namespace Messaging;

Request::Request(std::string requestType, std::string sender,
  std::string resource) :
  requestType(requestType), sender(sender),
  resource(resource) {
}

Request::Request(std::string requestType, std::string sender,
  std::string resource, IEntity::Shared content) :
  requestType(requestType), sender(sender),
  resource(resource), content(content) {
}
