#include "Event.hpp"

using namespace Messaging;

Event::Event(EventType eventType, std::string resource) :
  eventType(eventType), resource(resource) {
}

Event::Event(EventType eventType, std::string resource, std::unique_ptr<IEntity> content) :
  eventType(eventType), resource(resource), content(std::move(content)) {
}
