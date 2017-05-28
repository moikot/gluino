#include "Utils/Testing.hpp"

#include "Core/Memory.hpp"
#include "Messaging/IMessageQueue.hpp"
#include "FakeMessageQueue.hpp"

using namespace Core;
using namespace Messaging;

using namespace fakeit;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

  struct EventSink {
    virtual void onResponse(const Response&) = 0;
    virtual void onEvent(const Event&) const = 0;
  };

}

TEST_CASE("queue generic client can send a request", "[QueueGenericClient]") {
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
  auto client = std::make_unique<QueueGenericClient>("clientId", mq);

  client->sendRequest(RequestType::Read, "resource", std::move(content));

  Verify(Method(messageQueue, addRequest));
}

TEST_CASE("queue generic client can process a response", "[QueueGenericClient]") {
  Mock<IMessageQueue> messageQueue;
  When(Method(messageQueue, removeClient)).Do([](const QueueClient&) {});
  {
    auto client = std::make_unique<QueueGenericClient>("id", messageQueue.get());
    auto content = std::make_unique<Status>(Status::OK);
    auto contentPtr = content.get();

    Mock<EventSink> eventSink;
    When(Method(eventSink, onResponse)).Do([=](const Response& response) {
      REQUIRE(response.getRequestType() == RequestType::Read);
      REQUIRE(response.getReceiver() == "receiver");
      REQUIRE(response.getResource() == "resource");
      REQUIRE(&response.getContent() == contentPtr);
      return Status::OK;
    });

    client->setOnResponse([&](const Response& e) { eventSink.get().onResponse(e); });

    Response response("id", "receiver", RequestType::Read, "resource", std::move(content));
    client->onResponse(response);

    Verify(Method(eventSink, onResponse));
  }
  Verify(Method(messageQueue, removeClient));
}

TEST_CASE("queue generic client can process an event", "[QueueGenericClient]") {
  Mock<IMessageQueue> messageQueue;
  When(Method(messageQueue, removeClient)).Do([](const QueueClient&) {});
  {
    auto client = std::make_shared<QueueGenericClient>("id", messageQueue.get());
    auto content = std::make_unique<Content>();
    auto contentPtr = content.get();

    Mock<EventSink> eventSink;
    When(Method(eventSink, onEvent)).Do([=](const Event& event) {
      REQUIRE(event.getEventType() == EventType::Created);
      REQUIRE(event.getResource() == "resource");
      REQUIRE(event.getContent() == contentPtr);
      return Status::OK;
    });

    client->setOnEvent([&](const Event& e) { eventSink.get().onEvent(e); });

    Event event(EventType::Created, "resource", std::move(content));
    client->onEvent(event);

    Verify(Method(eventSink, onEvent));
  }
  Verify(Method(messageQueue, removeClient));
}
