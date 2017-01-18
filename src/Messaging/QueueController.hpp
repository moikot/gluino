// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_QUEUE_CONTROLLER_HPP
#define MESSAGING_QUEUE_CONTROLLER_HPP

#include "Request.hpp"
#include "Event.hpp"
#include "Core/StatusResult.hpp"

#include <functional>

namespace Messaging {

class IMessageQueue;

typedef std::function<Core::IEntity::Unique(const Request&)> RequestHandler;

class QueueController {
  TYPE_PTRS(QueueController)
  public:
    QueueController(IMessageQueue& messageQueue);

    RequestHandler onRequest(const Request& request);

    void setRequestHandler(std::function<RequestHandler(const Request&)> handler) {
      this->requestHandler = handler;
    }

  private:
    IMessageQueue& messageQueue;
    std::function<RequestHandler(const Request&)> requestHandler;
};

}

#endif /* end of include guard: MESSAGING_QUEUE_CONTROLLER_HPP */
