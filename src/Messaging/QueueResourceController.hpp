// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_QUEUE_RESOURCE_CONTROLLER_HPP
#define MESSAGING_QUEUE_RESOURCE_CONTROLLER_HPP

#include "QueueController.hpp"

namespace Messaging {

class IMessageQueue;

class QueueResourceController {
  TYPE_PTRS(QueueResourceController)
  public:
    QueueResourceController(std::string resource, QueueController& queueController);

    Core::StatusResult::Unique sendEvent(std::string eventType);
    Core::StatusResult::Unique sendEvent(std::string eventType, Core::IEntity::Unique content);

  private:
    const std::string resource;
    QueueController& queueController;

    RequestHandler getRequestHandler(const Request& request);
};

}

#endif /* end of include guard: MESSAGING_QUEUE_RESOURCE_CONTROLLER_HPP */
