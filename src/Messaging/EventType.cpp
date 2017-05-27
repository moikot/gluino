#include "EventType.hpp"

using namespace Messaging;

EventType EventType::Created("created");
EventType EventType::Updated("updated");
EventType EventType::Deleted("deleted");

EventType::EventType(const std::string& eventType) : eventType(eventType) {
}
