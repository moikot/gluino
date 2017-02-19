#include "QueueGenericClient.hpp"
#include "IMessageQueue.hpp"
#include "Core/Casting.hpp"

using namespace Core;
using namespace Messaging;

QueueGenericClient::QueueGenericClient(std::string clientId, IMessageQueue& messageQueue) :
  clientId(clientId), messageQueue(messageQueue) {
}

QueueGenericClient::~QueueGenericClient() {
  messageQueue.removeClient(*this);
}

Status
QueueGenericClient::sendRequest(std::string requestType, std::string resource, std::unique_ptr<IEntity> content) {
	auto request = std::make_unique<Request>(clientId, requestType, resource, std::move(content));
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
