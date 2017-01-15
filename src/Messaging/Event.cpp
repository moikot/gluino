#include "Event.hpp"

using namespace Messaging;

Event::Event(
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
