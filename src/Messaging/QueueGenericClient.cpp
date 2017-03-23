#include "QueueGenericClient.hpp"
#include "IMessageQueue.hpp"
#include "Core/Memory.hpp"
#include "Core/Identity.hpp"

using namespace Core;
using namespace Messaging;

QueueGenericClient::QueueGenericClient(std::string clientId, IMessageQueue& messageQueue) :
  clientId(clientId), messageQueue(messageQueue) {
}

QueueGenericClient::~QueueGenericClient() {
  messageQueue.removeClient(*this);
}

std::tuple<Core::Status, std::string>
QueueGenericClient::sendRequest(RequestType requestType, std::string resource, std::unique_ptr<IEntity> content) {
  auto id = Identity::create();
	auto request = std::make_unique<Request>(id, clientId, requestType, resource, std::move(content));
	return std::make_tuple(messageQueue.addRequest(std::move(request)), id);
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
