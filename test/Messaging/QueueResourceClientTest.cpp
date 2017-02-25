#include "Utils/Testing.hpp"

#include "Core/Memory.hpp"
#include "Messaging/IMessageQueue.hpp"
#include "FakeMessageQueue.h"

using namespace Core;
using namespace Messaging;

using namespace fakeit;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

  struct EventSink {
    virtual void onResponse(const Status&) = 0;
    virtual void onEvent(const Content&) const = 0;
  };

}

TEST_CASE("queue resource client can send a request", "[QueueResourceClient]") {
  Mock<IMockableMessageQueue> messageQueue;

  When(Method(messageQueue, addRequest)).Do([=](const Request& request) {
    REQUIRE(request.getRequestType() == RequestType::Read);
    REQUIRE(request.getSender() == "clientId");
    REQUIRE(request.getResource() == "resource");
    REQUIRE(request.getContent() == nullptr);
    return Status::OK;
  });

  FakeMessageQueue mq(messageQueue.get());
  auto client = std::make_unique<QueueResourceClient>("clientId", "resource", mq);
  client->sendRequest(RequestType::Read);

  Verify(Method(messageQueue, addRequest));
}

TEST_CASE("queue resource client can send a request with content", "[QueueResourceClient]") {
  Mock<IMockableMessageQueue> messageQueue;
  auto content = std::make_unique<Content>();
  auto contentPtr = content.get();

  When(Method(messageQueue, addRequest)).Do([=](const Request& request) {
    REQUIRE(request.getRequestType() == RequestType::Read);
    REQUIRE(request.getSender() == "clientId");
    REQUIRE(request.getResource() == "resource");
    REQUIRE(request.getContent() == contentPtr);
    return Status::OK;
  });

  FakeMessageQueue mq(messageQueue.get());
  auto client = std::make_unique<QueueResourceClient>("clientId", "resource", mq);
  client->sendRequest(RequestType::Read, std::move(content));

  Verify(Method(messageQueue, addRequest));
}

TEST_CASE("queue resource client can process a response", "[QueueResourceClient]") {
  Mock<IMessageQueue> messageQueue;
  When(Method(messageQueue, removeClient)).Do([](const QueueClient&) {});
  {
    auto client = std::make_unique<QueueResourceClient>("id", "resource", messageQueue.get());
    auto result = std::make_unique<Status>(Status::OK);
    auto resultPtr = result.get();

    Mock<EventSink> eventSink;
    When(Method(eventSink, onResponse)).Do([=](const Status& result) {
      REQUIRE(&result == resultPtr);
      return Status::OK;
    });
    client->addOnResponse(RequestType::Read, [&](const Status& c){ return eventSink.get().onResponse(c); });

    Response response("receiver", RequestType::Read, "resource", std::move(result));
    client->onResponse(response);

    Verify(Method(eventSink, onResponse));
  }
  Verify(Method(messageQueue, removeClient));
}

TEST_CASE("queue resource client can process an event", "[QueueResourceClient]") {
  Mock<IMessageQueue> messageQueue;
  When(Method(messageQueue, removeClient)).Do([](const QueueClient&) {});
  {
    auto client = std::make_unique<QueueResourceClient>("id", "resource", messageQueue.get());
    auto content = std::make_unique<Content>();
    auto contentPtr = content.get();

    Mock<EventSink> eventSink;
    When(Method(eventSink, onEvent)).Do([=](const Content& param) {
      REQUIRE(&param == contentPtr);
      return Status::OK;
    });
    client->addOnEvent(EventType::Created, [&](const Content& c){ eventSink.get().onEvent(c); });

    Event event(EventType::Created, "resource", std::move(content));
    client->onEvent(event);

    Verify(Method(eventSink, onEvent));
  }
  Verify(Method(messageQueue, removeClient));
}
