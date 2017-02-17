#include "QueueGenericClient.hpp"
#include "IMessageQueue.hpp"

using namespace Core;
using namespace Messaging;

QueueGenericClient::QueueGenericClient(std::string clientId, IMessageQueue& messageQueue) :
  clientId(clientId), messageQueue(messageQueue) {
}

QueueGenericClient::~QueueGenericClient() {
  messageQueue.removeClient(*this);
}

Status
QueueGenericClient::sendRequest(std::string requestType, std::string resource, IEntity::Unique content) {
	auto request = Request::makeUnique(clientId, requestType, resource, std::move(content));
	return messageQueue.addRequest(std::move(request));
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
