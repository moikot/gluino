// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_QUEUE_GENERIC_CLIENT_HPP
#define MESSAGING_QUEUE_GENERIC_CLIENT_HPP

#include "QueueClient.hpp"
#include "Core/Status.hpp"

#include <functional>

namespace Messaging {

class IMessageQueue;

class QueueGenericClient : public QueueClient {
  TYPE_PTRS(QueueGenericClient)
  public:
    QueueGenericClient(std::string clientId, IMessageQueue& messageQueue);

    std::string getClientId() const override { return clientId; }

  	Core::Status sendRequest(std::string requestType,
  		std::string resource, Core::IEntity::Unique content
  	);

    void onResponse(const Response& response) const override;
    void onEvent(const Event& event) const override;

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

#endif /* end of include guard: MESSAGING_QUEUE_GENERIC_CLIENT_HPP */
