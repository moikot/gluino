// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_QUEUE_CLIENT_HPP
#define MESSAGING_QUEUE_CLIENT_HPP

#include "Core/StatusResult.hpp"
#include "Response.hpp"
#include "Event.hpp"

#include <functional>

namespace Messaging {

class IMessageQueue;

class QueueClient {
  TYPE_PTRS(QueueClient)
  public:
    QueueClient(std::string clientId, IMessageQueue& messageQueue);

    std::string getId() { return clientId; }

    Core::StatusResult::Unique sendRequest(
        std::string type,
        std::string resource,
        Core::IEntity::Unique content
      );

    void onResponse(const Response& response);
    void onEvent(const Event& event);

    void setOnResponse(std::function<void(const Response&)> onResponse) {
      onResponseHandler = onResponse;
    }

    void setOnEvent(std::function<void(const Event&)> onEvent) {
      onEventHandler = onEvent;
    }

  private:
    std::string clientId;
    IMessageQueue& messageQueue;
    std::function<void(const Response&)> onResponseHandler;
    std::function<void(const Event&)> onEventHandler;
};

}

#endif /* end of include guard: MESSAGING_QUEUE_CLIENT_HPP */
