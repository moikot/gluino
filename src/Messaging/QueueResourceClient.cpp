#include "QueueResourceClient.hpp"
#include "IMessageQueue.hpp"

using namespace Messaging;

QueueResourceClient::QueueResourceClient(std::string clientId, std::string resource, IMessageQueue& messageQueue) :
  clientId(clientId), resource(resource), messageQueue(messageQueue) {
}

Core::Status::Unique
QueueResourceClient::sendRequest(std::string requestType) {
  auto request = Request::makeShared(requestType, clientId, resource, nullptr);
  return messageQueue.addRequest(request);
}

Core::Status::Unique
QueueResourceClient::sendRequest(std::string requestType, Core::IEntity::Shared content) {
  auto request = Request::makeShared(requestType, clientId, resource, content);
  return messageQueue.addRequest(request);
}

void
QueueResourceClient::onResponse(const Response& response) const {
  if (response.getResource() != resource) {
    return;
  }

  auto requestType = response.getRequestType();
  auto contentType = response.getContent().getTypeId();

  for (auto& handler : responseHandlers) {
    if (handler->getRequestType() == requestType &&
        handler->getContentType() == contentType) {
      handler->processResponse(response);
    }
  }
}

void
QueueResourceClient::onEvent(const Event& event) const {
  if (event.getResource() != resource) {
    return;
  }

  auto eventType = event.getEventType();
  std::string contentType;
  if (event.getContent())
    contentType = event.getContent()->getTypeId();

  for (auto& handler : eventHandlers) {
    if (handler->getEventType() == eventType &&
        handler->getContentType() == contentType) {
      handler->processEvent(event);
    }
  }
}
