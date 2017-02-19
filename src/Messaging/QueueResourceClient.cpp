#include "QueueResourceClient.hpp"
#include "IMessageQueue.hpp"
#include "Core/Memory.hpp"

using namespace Core;
using namespace Messaging;

QueueResourceClient::QueueResourceClient(std::string clientId, std::string resource, IMessageQueue& messageQueue) :
  clientId(clientId), resource(resource), messageQueue(messageQueue) {
}

QueueResourceClient::~QueueResourceClient() {
  messageQueue.removeClient(*this);
}

Core::Status
QueueResourceClient::sendRequest(std::string requestType) {
  auto request = std::make_unique<Request>(clientId, requestType, resource);
  return messageQueue.addRequest(std::move(request));
}

Core::Status
QueueResourceClient::sendRequest(std::string requestType, std::unique_ptr<IEntity> content) {
  auto request = std::make_unique<Request>(clientId, requestType, resource, std::move(content));
  return messageQueue.addRequest(std::move(request));
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
