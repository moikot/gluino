#include "QueueResourceController.hpp"

using namespace Core;
using namespace Messaging;

using namespace std::placeholders;

QueueResourceController::QueueResourceController(std::string resource, QueueController& queueController) :
  resource(resource), queueController(queueController) {
  queueController.setRequestHandler(
    std::bind(&QueueResourceController::getRequestHandler, this, _1));
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
  if (request.getResource() != resource) {
    return nullptr;
  }

  auto requestType = request.getRequestType();
  std::string contentType;
  if (request.getContent())
    contentType = request.getContent()->getTypeId();

  return getResourceRequestHandler(requestType, contentType);
}

RequestHandler
QueueResourceController::getResourceRequestHandler(std::string requestType, std::string contentType) {

  for(auto& handler: handlers) {
    if (handler->getRequestType() == requestType &&
        handler->getContentType() == contentType) {
          return std::bind(&IResourceRequestHandler::makeRequest, handler.get(), _1);
        }
  }
  return nullptr;
}
