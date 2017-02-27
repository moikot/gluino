// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_I_MESSAGE_QUEUE_HPP
#define MESSAGING_I_MESSAGE_QUEUE_HPP

#include "QueueGenericClient.hpp"
#include "QueueResourceClient.hpp"
#include "QueueResourceController.hpp"

namespace Messaging {

/**
  The message queue interface.
*/
struct IMessageQueue {
    virtual ~IMessageQueue() = default;

    /**
      Call this method to process messages.

    */
    virtual void idle() = 0;

    /**
      Adds a new request to the message queue.

      @param message The request to add to the queue.
      @return The result of the operation.
    */
    virtual Core::Status addRequest(std::unique_ptr<Request> request) = 0;

    /**
      Adds a new event to the message queue.

      @param message The event to add to the queue.
      @return The result of the operation.
    */
    virtual Core::Status addEvent(std::unique_ptr<Event> event) = 0;

    /**
      Creates a new queue client for sending requests and getting responses.

      @param clientId The unique client identifier.
      @return The queue client.
    */
    virtual std::unique_ptr<QueueGenericClient> createClient(std::string clinetId) = 0;

    /**
      Creates a new queue client for sending requests and getting responses.

      @param clientId The unique client identifier.
      @param clientId The resource identifier.
      @return The queue client.
    */
    virtual std::unique_ptr<QueueResourceClient> createClient(std::string clinetId, std::string resource) = 0;

    /**
      Removes a queue client from the queue.

      @param client The client to remove.
    */
    virtual void removeClient(const QueueClient& client) = 0;

    /**
      Creates a new queue controller for receiving requests and sending responses.

      @param clientId The unique controller identifier.
      @return The queue client.
    */
    virtual std::unique_ptr<QueueResourceController> createController(std::string resource) = 0;

    /**
      Removes a queue controller from the queue.

      @param client The client to remove.
    */
    virtual void removeController(const QueueResourceController& controller) = 0;
};

}

#endif /* end of include guard: MESSAGING_I_MESSAGE_QUEUE_HPP */
