#include "Response.hpp"

using namespace Core;
using namespace Messaging;

Response::Response(std::string sender, std::string receiver,
  ActionType actionType, std::string resource, ActionResult::Unique result) :
  Message(sender, receiver, actionType, resource, Priority::Mid),
  result(std::move(result)) {
}
