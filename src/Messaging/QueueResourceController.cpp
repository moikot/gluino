#include "QueueResourceController.hpp"
#include "IMessageQueue.hpp"

using namespace Core;
using namespace Messaging;

using namespace std::placeholders;

QueueResourceController::QueueResourceController(std::string resource, IMessageQueue& messageQueue) :
  resource(resource), messageQueue(messageQueue) {
}

Core::Status
QueueResourceController::sendEvent(std::string eventType) {
  auto event = Event::makeUnique(eventType, resource);
  return messageQueue.addEvent(std::move(event));
}

Core::Status
QueueResourceController::sendEvent(std::string eventType, Core::IEntity::Unique content) {
  auto event = Event::makeUnique(eventType, resource, std::move(content));
  return messageQueue.addEvent(std::move(event));
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

  for (auto& handler : handlers) {
    if (handler->getRequestType() == requestType &&
        handler->getContentType() == contentType) {
      return std::bind(&ResourceRequestHandler::makeRequest, handler.get(), _1);
    }
  }
  return nullptr;
}
