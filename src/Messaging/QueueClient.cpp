#include "QueueClient.hpp"
#include "IMessageQueue.hpp"

using namespace Core;
using namespace Messaging;

QueueClient::QueueClient(std::string clientId, IMessageQueue& messageQueue) :
  clientId(clientId), messageQueue(messageQueue) {
}

StatusResult::Unique
QueueClient::sendRequest(std::string type, std::string resource, IEntity::Unique content) {
  auto request = Request::makeShared(type, clientId, resource, std::move(content));
  return messageQueue.addRequest(request);
}

void
QueueClient::onResponse(const Response& response) {
  if (onResponseHandler) {
    onResponseHandler(response);
  }
}

void
QueueClient::onEvent(const Event& event) {
  if (onEventHandler) {
    onEventHandler(event);
  }
}
