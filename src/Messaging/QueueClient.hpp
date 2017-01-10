// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_QUEUE_CLIENT_HPP
#define MESSAGING_QUEUE_CLIENT_HPP

#include "Core/StatusResult.hpp"
#include "Message.hpp"
#include "Response.hpp"
#include "Notification.hpp"

#include <functional>

namespace Messaging {

class IMessageQueue;

class QueueClient {
  TYPE_PTRS(QueueClient)
  public:
    QueueClient(std::string clientId, IMessageQueue& messageQueue);

    std::string getId() { return clientId; }

    Core::StatusResult::Unique sendRequest(
        ActionType actionType,
        std::string resource,
        Core::IEntity::Unique content
      );

    void onResponse(const Response& response);
    void onNotification(const Notification& notification);

    void setOnResponse(std::function<void(const Response&)> onResponse) {
      onResponseHandler = onResponse;
    }

    void setOnNotification(std::function<void(const Notification&)> onNotification) {
      onNotificationHandler = onNotification;
    }

  private:
    std::string clientId;
    IMessageQueue& messageQueue;
    std::function<void(const Response&)> onResponseHandler;
    std::function<void(const Notification&)> onNotificationHandler;
};

}

#endif /* end of include guard: MESSAGING_QUEUE_CLIENT_HPP */
