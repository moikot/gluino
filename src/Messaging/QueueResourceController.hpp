// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_QUEUE_RESOURCE_CONTROLLER_HPP
#define MESSAGING_QUEUE_RESOURCE_CONTROLLER_HPP

#include "ResourceRequestHandler.hpp"
#include "EventType.hpp"
#include "Core/Status.hpp"
#include "Core/Memory.hpp"

#include <vector>

namespace Messaging {

struct IMessageQueue;

typedef std::function<std::unique_ptr<Core::IEntity>(const Request&)> RequestHandler;

class QueueResourceController {
  public:
    QueueResourceController(const std::string& resource, IMessageQueue& messageQueue);
    virtual ~QueueResourceController();

    QueueResourceController(const QueueResourceController&) = delete;
    QueueResourceController& operator=(const QueueResourceController&) = delete;

    Core::Status sendEvent(EventType eventType);
    Core::Status sendEvent(EventType eventType, std::unique_ptr<Core::IEntity> content);

    template<typename T>
    void addOnRequest(RequestType requestType, T onRequest) {
      handlers.push_back(std::make_unique<ResourceRequestHandlerImpl<T>>(requestType, onRequest));
    }

    RequestHandler getRequestHandler(const Request& request) const;

  private:
    const std::string resource;
    IMessageQueue& messageQueue;
    std::vector<std::unique_ptr<ResourceRequestHandler>> handlers;
};

}

#endif /* end of include guard: MESSAGING_QUEUE_RESOURCE_CONTROLLER_HPP */
