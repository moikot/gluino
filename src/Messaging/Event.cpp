#include "Event.hpp"

using namespace Messaging;

Event::Event(std::string eventType, std::string resource) :
  eventType(eventType), resource(resource) {
}

Event::Event(std::string eventType, std::string resource, IEntity::Unique content) :
  eventType(eventType), resource(resource), content(std::move(content)) {
}
