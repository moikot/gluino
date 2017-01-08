#include "QueueController.hpp"
#include "IMessageQueue.hpp"

using namespace Core;

QueueController::QueueController(std::string controllerId, IMessageQueue& messageQueue) :
  controllerId(controllerId), messageQueue(messageQueue) {

}

StatusResult::Unique
QueueController::sendNotification(std::string receiver, ActionType actionType,
  std::string resource, IEntity::Shared result) {
  auto notification = Notification::makeShared(controllerId, receiver, actionType, resource, result);
  return messageQueue.sendMessage(notification);
}

StatusResult::Unique
QueueController::broadcastNotification(ActionType actionType,
  std::string resource, IEntity::Shared result) {
  auto notification = Notification::makeShared(controllerId, "", actionType, resource, result);
  return messageQueue.sendMessage(notification);
}

bool
QueueController::canProcessRequest(const Request& request) {
  if (canProcessRequestHandler)
    return canProcessRequestHandler(request);
  return false;
}

ActionResult::Unique
QueueController::processRequest(const Request& request) {
  if (processRequestHandler)
    return processRequestHandler(request);
  return StatusResult::NotImplemented();
}
