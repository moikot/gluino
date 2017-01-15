#include "Event.hpp"

using namespace Messaging;

Event::Event(
  std::string eventType,
  std::string resource,
  IEntity::Shared content
) :
  eventType(eventType),
  resource(resource),
  content(content) {
}
