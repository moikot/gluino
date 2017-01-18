#include "QueueGenericClient.hpp"
#include "IMessageQueue.hpp"

using namespace Core;
using namespace Messaging;

QueueGenericClient::QueueGenericClient(std::string clientId, IMessageQueue& messageQueue) :
  clientId(clientId), messageQueue(messageQueue) {
}

void
QueueGenericClient::onResponse(const Response& response) const {
  if (onResponseHandler) {
    onResponseHandler(response);
  }
}

void
QueueGenericClient::onEvent(const Event& event) const {
  if (onEventHandler) {
    onEventHandler(event);
  }
}

StatusResult::Unique
QueueGenericClient::sendRequest(std::string requestType, std::string resource, IEntity::Shared content) {
  auto request = Request::makeShared(requestType, clientId, resource, content);
  return messageQueue.addRequest(request);
}
