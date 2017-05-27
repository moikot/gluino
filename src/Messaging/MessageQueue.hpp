// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_MESSAGE_QUEUE_HPP
#define MESSAGING_MESSAGE_QUEUE_HPP

#include "IMessageQueue.hpp"

#include <queue>
#include <list>

namespace Messaging {

/**
  The message queue.
*/
class MessageQueue : public IMessageQueue {
  public:
    /**
      This method should be called for dispatching the messages.
    */
    virtual void idle() override;

    /**
      Adds a request to the queue.
    */
    virtual Core::Status addRequest(std::unique_ptr<Request> request) override;

    /**
      Adds a event to the queue.
    */
    virtual Core::Status addEvent(std::unique_ptr<Event> event) override;

    /**
      Creates a queue client.
    */
    virtual std::unique_ptr<QueueGenericClient> createClient(std::string clinetId) override;

    /**
    Creates a queue client.
    */
    virtual std::unique_ptr<QueueResourceClient> createClient(std::string clinetId, std::string resource) override;

    /**
      Removes the queue client.
    */
    virtual void removeClient(const QueueClient& client) override;

    /**
      Creates a queue controller.
    */
    virtual std::unique_ptr<QueueResourceController> createController(std::string resource) override;

    /**
      Removes the queue controller.
    */
    virtual void removeController(const QueueResourceController& controller) override;

  private:
    std::queue<std::unique_ptr<Request>> requests;
    std::queue<std::unique_ptr<Response>> responses;
    std::queue<std::unique_ptr<Event>> events;

    std::list<const QueueClient*> clients;
    std::list<const QueueResourceController*> controllers;

    void processRequest(const Request& request);
    void processResponse(const Response& response);
    void processEvent(const Event& event);

    const QueueClient*  getClient(const std::string& clientId);
    RequestHandler      getRequestHandler(const Request& request);

    void sendResponseFor(const Request& request, std::unique_ptr<Core::IEntity> result);
};

}

#endif /* end of include guard: MESSAGING_MESSAGE_QUEUE_HPP */
