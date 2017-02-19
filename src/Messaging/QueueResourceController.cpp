#include "QueueResourceController.hpp"
#include "IMessageQueue.hpp"
#include "Core/Casting.hpp"

using namespace Core;
using namespace Messaging;

using namespace std::placeholders;

QueueResourceController::QueueResourceController(std::string resource, IMessageQueue& messageQueue) :
  resource(resource), messageQueue(messageQueue) {
}

QueueResourceController::~QueueResourceController() {
  messageQueue.removeController(*this);
}

Core::Status
QueueResourceController::sendEvent(std::string eventType) {
  auto event = std::make_unique<Event>(eventType, resource);
  return messageQueue.addEvent(std::move(event));
}

Core::Status
QueueResourceController::sendEvent(std::string eventType, std::unique_ptr<IEntity> content) {
  auto event = std::make_unique<Event>(eventType, resource, std::move(content));
  return messageQueue.addEvent(std::move(event));
}

RequestHandler
QueueResourceController::getRequestHandler(const Request& request) const {
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
