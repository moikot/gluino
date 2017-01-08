// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_I_MESSAGE_QUEUE_HPP
#define MESSAGING_I_MESSAGE_QUEUE_HPP

#include "Message.hpp"
#include "QueueClient.hpp"
#include "QueueController.hpp"
#include "Core/IService.hpp"

namespace Messaging {

/**
  The message queue interface.
*/
class IMessageQueue : public Core::IService {
  TYPE_PTRS_ABSTRACT(IMessageQueue)
  public:

    /**
      Adds a new message to the message queue.

      @param message The message to add to the queue.
      @return The result of the operation.
    */
    virtual Core::StatusResult::Unique sendMessage(Message::Shared message) = 0;

    /**
      Creates a new queue client for sending requests and getting responses.

      @param clientId The unique client identifier.
      @return The queue client.
    */
    virtual QueueClient::Shared createClient(std::string clinetId) = 0;

    /**
      Removes a queue client from the queue.

      @param client The client to remove.
    */
    virtual void removeClient(QueueClient::Shared client) = 0;

    /**
      Creates a new queue controller for receiving requests and sending responses.

      @param clientId The unique controller identifier.
      @return The queue client.
    */
    virtual QueueController::Shared createController(std::string controllerId) = 0;

    /**
      Removes a queue controller from the queue.

      @param client The client to remove.
    */
    virtual void removeController(QueueController::Shared controller) = 0;
};

}

#endif /* end of include guard: MESSAGING_I_MESSAGE_QUEUE_HPP */
