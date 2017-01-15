#include "Event.hpp"

using namespace Messaging;

Event::Event(
  std::string eventType,
  std::string sender,
  std::string resource,
  IEntity::Shared content
) :
  eventType(eventType),
  sender(sender),
  resource(resource),
  content(content) {
}
