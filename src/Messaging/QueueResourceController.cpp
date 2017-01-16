#include "QueueResourceController.hpp"

using namespace Core;
using namespace Messaging;

QueueResourceController::QueueResourceController(std::string resource, QueueController& queueController) :
  resource(resource), queueController(queueController) {
  queueController.setRequestHandler(
    std::bind(&QueueResourceController::getRequestHandler, this, std::placeholders::_1));
}

Core::StatusResult::Unique
QueueResourceController::sendEvent(std::string eventType) {
  return queueController.sendEvent(eventType, resource, nullptr);
}

Core::StatusResult::Unique
QueueResourceController::sendEvent(std::string eventType, Core::IEntity::Unique content) {
  return queueController.sendEvent(eventType, resource, std::move(content));
}

RequestHandler
QueueResourceController::getRequestHandler(const Request& request) {
  return nullptr;
}
