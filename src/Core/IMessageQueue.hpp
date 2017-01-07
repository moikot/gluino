// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_I_MESSAGE_QUEUE_HPP
#define CORE_I_MESSAGE_QUEUE_HPP

#include "ILoopedService.hpp"
#include "ActionResult.hpp"
#include "Message.hpp"
#include "QueueClient.hpp"
#include "QueueController.hpp"

#include <memory>
#include <functional>

namespace Core {

class IMessageQueue : public ILoopedService {
  TYPE_PTRS_ABSTRACT(IMessageQueue)
  public:
    virtual ~IMessageQueue();

    virtual StatusResult::Unique sendMessage(Message::Shared message) = 0;

    virtual QueueClient::Shared createClient(std::string clinetId) = 0;
    virtual void removeClient(QueueClient::Shared client) = 0;

    virtual QueueController::Shared createController(std::string controllerId) = 0;
    virtual void removeController(QueueController::Shared controller) = 0;
};

}

#endif /* end of include guard: CORE_I_MESSAGE_QUEUE_HPP */
