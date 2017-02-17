// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_MESSAGE_QUEUE_HPP
#define MESSAGING_MESSAGE_QUEUE_HPP

#include "IMessageQueue.hpp"
#include "Core/ILogger.hpp"

#include <queue>
#include <list>

namespace Messaging {

/**
  The message queue.
*/
class MessageQueue : public IMessageQueue {
  TYPE_PTRS(MessageQueue)
  public:
    explicit MessageQueue(Core::ILogger::Shared logger);

    /**
      This method should be called for dispatching the messages.
    */
    virtual void idle() override;

    /**
      Adds a request to the queue.
    */
    virtual Core::Status addRequest(Request::Unique request) override;

    /**
      Adds a event to the queue.
    */
    virtual Core::Status addEvent(Event::Unique event) override;

    /**
      Creates a queue client.
    */
    virtual QueueGenericClient::Unique createClient(std::string clinetId) override;

    /**
    Creates a queue client.
    */
    virtual QueueResourceClient::Unique createClient(std::string clinetId, std::string resource) override;

    /**
      Removes the queue client.
    */
    virtual void removeClient(const QueueClient& client) override;

    /**
      Creates a queue controller.
    */
    virtual QueueResourceController::Unique createController(std::string resource) override;

    /**
      Removes the queue controller.
    */
    virtual void removeController(const QueueResourceController& controller) override;

  private:
    Core::ILogger::Shared logger;
    std::queue<Request::Unique> requests;
    std::queue<Response::Unique> responses;
    std::queue<Event::Unique> events;

    std::list<const QueueClient*> clients;
    std::list<const QueueResourceController*> controllers;

    void processRequest(const Request& request);
    void processResponse(const Response& response);
    void processEvent(const Event& event);

    const QueueClient*  getClient(std::string clientId);
    RequestHandler      getRequestHandler(const Request& request);

    void sendResponseFor(
      const Request&          request,
      Core::IEntity::Unique   result
    );
};

}

#endif /* end of include guard: MESSAGING_MESSAGE_QUEUE_HPP */
