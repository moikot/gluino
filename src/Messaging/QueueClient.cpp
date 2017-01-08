#include "QueueClient.hpp"
#include "IMessageQueue.hpp"

using namespace Core;

QueueClient::QueueClient(std::string clientId, IMessageQueue& messageQueue) :
  clientId(clientId), messageQueue(messageQueue) {
}

StatusResult::Unique
QueueClient::sendMessage(Message::Shared request) {
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
