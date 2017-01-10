#include "Request.hpp"

using namespace Messaging;

Request::Request(std::string sender, ActionType actionType, std::string resource,
  IEntity::Unique content) : Message(sender, "", actionType, resource, Priority::High),
  content(std::move(content)) {
}
