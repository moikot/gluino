#include "Request.hpp"

using namespace Messaging;

Request::Request(
  std::string sender,
  ActionType actionType,
  std::string resource,
  IEntity::Shared content
) :
  sender(sender),
  actionType(actionType),
  resource(resource),
  content(content) {
}
