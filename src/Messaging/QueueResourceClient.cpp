#include "QueueResourceClient.hpp"

using namespace Messaging;

QueueResourceClient::QueueResourceClient(std::string resource, QueueClient& queueClient) :
  resource(resource), queueClient(queueClient) {

  queueClient.setOnResponse(
    std::bind(&QueueResourceClient::onResponse, this, std::placeholders::_1));
  queueClient.setOnEvent(
    std::bind(&QueueResourceClient::onEvent, this, std::placeholders::_1));
}

Core::StatusResult::Unique
QueueResourceClient::sendRequest(std::string requestType) {
  return queueClient.sendRequest(requestType, resource, nullptr);
}

Core::StatusResult::Unique
QueueResourceClient::sendRequest(std::string requestType, Core::IEntity::Unique content) {
  return queueClient.sendRequest(requestType, resource, std::move(content));
}

void
QueueResourceClient::onResponse(const Response& response) {
  if (response.getResource() != resource) {
    return;
  }

  auto requestType = response.getRequestType();
  auto contentType = response.getContent().getTypeId();

  for(auto& handler: responseHandlers) {
    if (handler->getRequestType() == requestType &&
        handler->getContentType() == contentType) {
          handler->processResponse(response);
        }
  }
}

void
QueueResourceClient::onEvent(const Event& event) {
  if (event.getResource() != resource) {
    return;
  }

  auto eventType = event.getEventType();
  std::string contentType;
  if (event.getContent())
    contentType = event.getContent()->getTypeId();

  for(auto& handler: eventHandlers) {
    if (handler->getEventType() == eventType &&
        handler->getContentType() == contentType) {
          handler->processEvent(event);
        }
  }
}
