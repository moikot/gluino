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
    virtual std::unique_ptr<IEntity> onRequest(const Content&) = 0;
  };

}

TEST_CASE("queue resource controller can send an event", "[QueueResourceController]") {
  Mock<IMockableMessageQueue> messageQueue;

  When(Method(messageQueue, addEvent)).Do([=](const Event& event) {
    REQUIRE(event.getEventType() == "created");
    REQUIRE(event.getResource() == "resource");
    REQUIRE(event.getContent() == nullptr);
    return Status::OK;
  });

  FakeMessageQueue mq(messageQueue.get());
  auto client = std::make_unique<QueueResourceController>("resource", mq);
  client->sendEvent("created");

  Verify(Method(messageQueue, addEvent));
}

TEST_CASE("queue resource controller can send an event with content", "[QueueResourceController]") {
  Mock<IMockableMessageQueue> messageQueue;
  auto content = std::make_unique<Content>();
  auto contentPtr = content.get();

  When(Method(messageQueue, addEvent)).Do([=](const Event& event) {
    REQUIRE(event.getEventType() == "created");
    REQUIRE(event.getResource() == "resource");
    REQUIRE(event.getContent() == contentPtr);
    return Status::OK;
  });

  FakeMessageQueue mq(messageQueue.get());
  auto client = std::make_unique<QueueResourceController>("resource", mq);
  client->sendEvent("created", std::move(content));

  Verify(Method(messageQueue, addEvent));
}

TEST_CASE("queue resource controller can process a request", "[QueueResourceController]") {
  Mock<IMessageQueue> messageQueue;
  When(Method(messageQueue, removeController)).Do([](const QueueResourceController&) {});
  {
    auto client = std::make_unique<QueueResourceController>("resource", messageQueue.get());
    auto content = std::make_unique<Content>();
    auto contentPtr = content.get();

    Mock<EventSink> eventSink;
    When(Method(eventSink, onRequest)).Do([=](const Content& param) {
      REQUIRE(&param == contentPtr);
      return std::make_unique<Status>(Status::OK);
    });
    client->addOnRequest("create", [&](const Content& c) { return eventSink.get().onRequest(c); });

    Request request("sender", "create", "resource", std::move(content));
    auto handler = client->getRequestHandler(request);
    REQUIRE(handler != nullptr);

    auto response = handler(request);
    REQUIRE(response != nullptr);

    Verify(Method(eventSink, onRequest));
  }
  Verify(Method(messageQueue, removeController));
}

TEST_CASE("queue resource controller cannot process a request for another resource", "[QueueResourceController]") {
  Mock<IMessageQueue> messageQueue;
  When(Method(messageQueue, removeController)).Do([](const QueueResourceController&) {});
  auto client = std::make_unique<QueueResourceController>("resource", messageQueue.get());

  Request request("create", "sender", "another resource");
  auto handler = client->getRequestHandler(request);

  REQUIRE(handler == nullptr);
}
