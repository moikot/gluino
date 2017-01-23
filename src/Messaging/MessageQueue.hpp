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
    virtual Core::Status addRequest(Request::Shared request) override;

    /**
      Adds a event to the queue.
    */
    virtual Core::Status addEvent(Event::Shared event) override;

    /**
      Creates a queue client.
    */
    virtual QueueGenericClient::Shared createClient(std::string clinetId) override;

    /**
    Creates a queue client.
    */
    virtual QueueResourceClient::Shared createClient(std::string clinetId, std::string resource) override;

    /**
      Removes the queue client.
    */
    virtual void removeClient(QueueClient::Shared client) override;

    /**
      Creates a queue controller.
    */
    virtual QueueResourceController::Shared createController(std::string resource) override;

    /**
      Removes the queue controller.
    */
    virtual void removeController(QueueResourceController::Shared controller) override;

  private:
    Core::ILogger::Shared logger;
    std::queue<Request::Shared> requests;
    std::queue<Response::Shared> responses;
    std::queue<Event::Shared> events;

    std::list<QueueClient::Shared> clients;
    std::list<QueueResourceController::Shared> controllers;

    void processRequest(const Request& request);
    void processResponse(const Response& response);
    void processEvent(const Event& event);

    QueueClient::Shared   getClient(std::string clientId);
    RequestHandler        getRequestHandler(const Request& request);

    void sendResponseFor(
      const Request&          request,
      Core::IEntity::Unique   result
    );
};

}

#endif /* end of include guard: MESSAGING_MESSAGE_QUEUE_HPP */
