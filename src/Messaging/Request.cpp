#include "Request.hpp"

using namespace Messaging;

Request::Request(std::string sender, Request::Unique request) :
  Message(sender, "", request->getActionType(), request->getResource(), Priority::High),
  content(std::move(request->content)) {
}

Request::Request(ActionType actionType, std::string resource, IEntity::Unique content) :
  Message("", "", actionType, resource, Priority::High),
  content(std::move(content)) {
}

Request::Request(std::string sender, ActionType actionType, std::string resource) :
  Message(sender, "", actionType, resource, Priority::High) {

}

Request::Request(std::string sender, ActionType actionType, std::string resource,
  IEntity::Unique content) : Message(sender, "", actionType, resource, Priority::High),
  content(std::move(content)) {
}
