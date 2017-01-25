#include "QueueGenericClient.hpp"
#include "IMessageQueue.hpp"

using namespace Core;
using namespace Messaging;

QueueGenericClient::QueueGenericClient(std::string clientId, IMessageQueue& messageQueue) :
  clientId(clientId), messageQueue(messageQueue) {
}

Status
QueueGenericClient::sendRequest(std::string requestType, std::string resource, IEntity::Unique content) {
	auto request = Request::makeShared(clientId, requestType, resource, std::move(content));
	return messageQueue.addRequest(request);
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
