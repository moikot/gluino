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

RequestFunction
QueueResourceController::getRequestHandler(const Request& request) {
  if (request.getResource() != resource) {
    return nullptr;
  }

  auto requestType = request.getRequestType();
  std::string contentType;
  if (request.getContent())
    contentType = request.getContent()->getTypeId();

  return getRequestHandler2(requestType, contentType);
}

RequestFunction
QueueResourceController::getRequestHandler2(std::string requestType, std::string contentType) {
  return nullptr;
}
