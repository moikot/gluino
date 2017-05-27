#include "QueueResourceClient.hpp"
#include "IMessageQueue.hpp"
#include "Core/Memory.hpp"
#include "Core/Identity.hpp"

using namespace Core;
using namespace Messaging;

QueueResourceClient::QueueResourceClient(const std::string& clientId, std::string resource, IMessageQueue& messageQueue) :
  clientId(clientId), resource(resource), messageQueue(messageQueue) {
}

QueueResourceClient::~QueueResourceClient() {
  messageQueue.removeClient(*this);
}

std::tuple<Core::Status, std::string>
QueueResourceClient::sendRequest(RequestType requestType) {
  auto id = Identity::create();
  auto request = std::make_unique<Request>(id, clientId, requestType, resource);
  return std::make_tuple(messageQueue.addRequest(std::move(request)), id);
}

std::tuple<Core::Status, std::string>
QueueResourceClient::sendRequest(RequestType requestType, std::unique_ptr<IEntity> content) {
  auto id = Identity::create();
  auto request = std::make_unique<Request>(id, clientId, requestType, resource, std::move(content));
  return std::make_tuple(messageQueue.addRequest(std::move(request)), id);
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
