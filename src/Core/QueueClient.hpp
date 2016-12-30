// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_QUEUE_CLIENT_HPP
#define CORE_QUEUE_CLIENT_HPP

#include "StatusResult.hpp"
#include "Message.hpp"
#include "Response.hpp"
#include "Notification.hpp"

#include <functional>

namespace Core {

class IMessageQueue;

class QueueClient {
  TYPE_PTRS(QueueClient)
  public:
    QueueClient(std::string clientId, IMessageQueue& messageQueue);

    std::string getId() { return clientId; }

    StatusResult::Unique sendMessage(Message::Shared request);

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

#endif /* end of include guard: CORE_QUEUE_CLIENT_HPP */
