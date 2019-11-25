#ifndef FAKE_MESSAGE_QUEUE
#define FAKE_MESSAGE_QUEUE

#include "Messaging/IMessageQueue.hpp"

namespace Messaging {

  struct IMockableMessageQueue {
    virtual Core::Status addRequest(const Request& request) = 0;
    virtual Core::Status addEvent(const Event& event) = 0;
  };

  struct FakeMessageQueue : public Messaging::IMessageQueue {
		explicit FakeMessageQueue(IMockableMessageQueue& queue) : queue(queue) {
	  }

    virtual void idle() override {
    }

    virtual Core::Status addRequest(std::unique_ptr<Request> request) override {
      return queue.addRequest(*request);
    }

    virtual Core::Status addEvent(std::unique_ptr<Event> event) override {
      return queue.addEvent(*event);
    }

    virtual std::unique_ptr<QueueGenericClient> createClient(std::string) override {
      return nullptr;
    }

    virtual std::unique_ptr<QueueResourceClient> createClient(std::string, std::string) override {
      return nullptr;
    }

    virtual void removeClient(const QueueClient&) override {
    }

    virtual std::unique_ptr<QueueResourceController> createController(std::string) override {
      return nullptr;
    }

    virtual void removeController(const QueueResourceController&) override {
    }

  private:
	  IMockableMessageQueue& queue;
  };

}

#endif /* end of include guard: FAKE_MESSAGE_QUEUE */
