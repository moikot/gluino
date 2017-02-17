#ifndef FAKE_MESSAGE_QUEUE
#define FAKE_MESSAGE_QUEUE

#include "Messaging/IMessageQueue.hpp"

namespace Messaging {

  struct IMockableMessageQueue {
    virtual Core::Status addRequest(const Request& request) = 0;
    virtual Core::Status addEvent(const Event& event) = 0;
  };

  struct FakeMessageQueue : public Messaging::IMessageQueue {
	  TYPE_PTRS(FakeMessageQueue)

		explicit FakeMessageQueue(IMockableMessageQueue& queue) : queue(queue) {
	  }

    virtual void idle() override {
    }

    virtual Core::Status addRequest(Request::Unique request) override {
      return queue.addRequest(*request);
    }

    virtual Core::Status addEvent(Event::Unique event) override {
      return queue.addEvent(*event);
    }

    virtual QueueGenericClient::Unique createClient(std::string clinetId) {
      return nullptr;
    }

    virtual QueueResourceClient::Unique createClient(std::string clinetId, std::string resource) {
      return nullptr;
    }

    virtual void removeClient(const QueueClient& client) {
    }

    virtual QueueResourceController::Unique createController(std::string resource) {
      return nullptr;
    }

    virtual void removeController(const QueueResourceController& controller) {
    }

  private:
	  IMockableMessageQueue& queue;
  };

}

#endif /* end of include guard: FAKE_MESSAGE_QUEUE */
