#include "QueueController.hpp"
#include "IMessageQueue.hpp"

using namespace Core;
using namespace Messaging;

QueueController::QueueController(IMessageQueue& messageQueue) : messageQueue(messageQueue) {
}

StatusResult::Unique
QueueController::sendEvent(std::string type,
  std::string resource, IEntity::Shared result) {
  auto event = Event::makeShared(type, resource, result);
  return messageQueue.addEvent(event);
}

RequestHandler
QueueController::getRequestHandler(const Request& request) {
  if (requestHandler)
    return requestHandler(request);
  return nullptr;
}
