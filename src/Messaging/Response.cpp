#include "Response.hpp"

using namespace Core;
using namespace Messaging;

Response::Response(std::string sender, std::string receiver,
  ActionType actionType, std::string resource, IEntity::Unique content) :
  Message(sender, receiver, actionType, resource, Priority::Mid),
  content(std::move(content)) {
}
