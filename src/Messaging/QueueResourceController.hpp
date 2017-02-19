// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_QUEUE_RESOURCE_CONTROLLER_HPP
#define MESSAGING_QUEUE_RESOURCE_CONTROLLER_HPP

#include "ResourceRequestHandler.hpp"
#include "Core/Status.hpp"

#include <vector>

namespace Messaging {

class IMessageQueue;

typedef std::function<std::unique_ptr<Core::IEntity>(const Request&)> RequestHandler;

class QueueResourceController {
  public:
    QueueResourceController(std::string resource, IMessageQueue& messageQueue);
    virtual ~QueueResourceController();

    QueueResourceController(const QueueResourceController&) = delete;
    QueueResourceController& operator=(const QueueResourceController&) = delete;

    Core::Status sendEvent(std::string eventType);
    Core::Status sendEvent(std::string eventType, std::unique_ptr<Core::IEntity> content);

    template<typename T>
    void addOnRequest(std::string requestType, T onRequest) {
      handlers.push_back(Core::makeUnique<ResourceRequestHandlerImpl<T>>(requestType, onRequest));
    }

    RequestHandler getRequestHandler(const Request& request) const;

  private:
    const std::string resource;
    IMessageQueue& messageQueue;
    std::vector<std::unique_ptr<ResourceRequestHandler>> handlers;
};

}

#endif /* end of include guard: MESSAGING_QUEUE_RESOURCE_CONTROLLER_HPP */
