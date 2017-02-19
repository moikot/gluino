#include "Request.hpp"

using namespace Messaging;

Request::Request(std::string sender, std::string requestType,
  std::string resource) :
  sender(sender), requestType(requestType),
  resource(resource) {
}

Request::Request(std::string sender, std::string requestType,
  std::string resource, std::unique_ptr<IEntity> content) :
  sender(sender), requestType(requestType),
  resource(resource), content(std::move(content)) {
}