#include "QueueController.hpp"
#include "IMessageQueue.hpp"

using namespace Core;
using namespace Messaging;

QueueController::QueueController(std::string controllerId, IMessageQueue& messageQueue) :
  controllerId(controllerId), messageQueue(messageQueue) {

}

StatusResult::Unique
QueueController::sendEvent(std::string type,
  std::string resource, IEntity::Shared result) {
  auto event = Event::makeShared(type, controllerId, resource, result);
  return messageQueue.addEvent(event);
}

bool
QueueController::canProcessRequest(const Request& request) {
  if (canProcessRequestHandler)
    return canProcessRequestHandler(request);
  return false;
}

IEntity::Unique
QueueController::processRequest(const Request& request) {
  if (processRequestHandler)
    return processRequestHandler(request);
  return StatusResult::NotImplemented();
}
