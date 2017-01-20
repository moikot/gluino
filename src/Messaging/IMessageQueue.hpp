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
#include "Core/IService.hpp"

namespace Messaging {

/**
  The message queue interface.
*/
class IMessageQueue : public Core::IService {
  TYPE_PTRS_ABSTRACT(IMessageQueue)
  public:

    /**
      Adds a new request to the message queue.

      @param message The request to add to the queue.
      @return The result of the operation.
    */
    virtual Core::Status::Unique addRequest(Request::Shared request) = 0;

    /**
      Adds a new event to the message queue.

      @param message The event to add to the queue.
      @return The result of the operation.
    */
    virtual Core::Status::Unique addEvent(Event::Shared event) = 0;

    /**
      Creates a new queue client for sending requests and getting responses.

      @param clientId The unique client identifier.
      @return The queue client.
    */
    virtual QueueGenericClient::Shared createGenericClient(std::string clinetId) = 0;

    /**
    Removes a queue client from the queue.

    @param client The client to remove.
    */
    virtual void removeGenericClient(QueueGenericClient::Shared client) = 0;

    /**
    Creates a new queue client for sending requests and getting responses.

    @param clientId The unique client identifier.
    @param clientId The resource identifier.
    @return The queue client.
    */
    virtual QueueResourceClient::Shared createResourceClient(std::string clinetId, std::string resource) = 0;

    /**
      Removes a queue client from the queue.

      @param client The client to remove.
    */
    virtual void removeResourceClient(QueueResourceClient::Shared client) = 0;

    /**
      Creates a new queue controller for receiving requests and sending responses.

      @param clientId The unique controller identifier.
      @return The queue client.
    */
    virtual QueueResourceController::Shared createResourceController(std::string resource) = 0;

    /**
      Removes a queue controller from the queue.

      @param client The client to remove.
    */
    virtual void removeResourceController(QueueResourceController::Shared controller) = 0;
};

}

#endif /* end of include guard: MESSAGING_I_MESSAGE_QUEUE_HPP */
