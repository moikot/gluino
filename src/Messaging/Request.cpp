#include "Request.hpp"

using namespace Messaging;

Request::Request(std::string sender, std::string requestType,
  std::string resource) :
  sender(sender), requestType(requestType),
  resource(resource) {
}

Request::Request(std::string sender, std::string requestType,
  std::string resource, IEntity::Unique content) :
  sender(sender), requestType(requestType),
  resource(resource), content(std::move(content)) {
}

Request::Request(std::string sender, Request&& request) : 
	Request(std::move(request)) {
	this->sender = sender;
}
