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

  // Go through all the response handlers
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

  // Go through all the event handlers
}

}
