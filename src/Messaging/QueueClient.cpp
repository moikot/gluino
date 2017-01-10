#include "QueueClient.hpp"
#include "IMessageQueue.hpp"

using namespace Core;
using namespace Messaging;

QueueClient::QueueClient(std::string clientId, IMessageQueue& messageQueue) :
  clientId(clientId), messageQueue(messageQueue) {
}

StatusResult::Unique
QueueClient::sendRequest(ActionType actionType, std::string resource, IEntity::Unique content) {
  auto request = Request::makeShared(clientId, actionType, resource, std::move(content));
  return messageQueue.sendMessage(request);
}

void
QueueClient::onResponse(const Response& response) {
  if (onResponseHandler)
    onResponseHandler(response);
}

void
QueueClient::onNotification(const Notification& notification) {
  if (onNotificationHandler)
    onNotificationHandler(notification);
}
