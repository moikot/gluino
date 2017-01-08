// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_QUEUE_CONTROLLER_HPP
#define MESSAGING_QUEUE_CONTROLLER_HPP

#include "Request.hpp"
#include "Notification.hpp"
#include "Core/ActionResult.hpp"
#include "Core/StatusResult.hpp"

#include <functional>

namespace Messaging {

class IMessageQueue;

class QueueController {
  TYPE_PTRS(QueueController)
  public:
    QueueController(std::string controllerId, IMessageQueue& messageQueue);

    std::string getId() const { return controllerId; }

    Core::StatusResult::Unique sendNotification(std::string receiver,
      ActionType actionType, std::string resource, Core::IEntity::Shared result);

    Core::StatusResult::Unique broadcastNotification(ActionType actionType,
      std::string resource, Core::IEntity::Shared result);

    bool canProcessRequest(const Request& request);
    Core::ActionResult::Unique processRequest(const Request& request);

    void setCanProcessRequest(std::function<bool(const Request&)> handler) {
      this->canProcessRequestHandler = handler;
    }
    void setProcessRequest(std::function<Core::ActionResult::Unique(const Request&)> handler) {
      this->processRequestHandler = handler;
    }

  private:
    std::string controllerId;
    IMessageQueue& messageQueue;
    std::function<bool(const Request&)> canProcessRequestHandler;
    std::function<Core::ActionResult::Unique(const Request&)> processRequestHandler;
};

}

#endif /* end of include guard: MESSAGING_QUEUE_CONTROLLER_HPP */