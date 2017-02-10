#include "Utils/Testing.hpp" 

#include "Messaging/IMessageQueue.hpp"
#include "FakeMessageQueue.h"

using namespace Core;
using namespace Messaging;

using namespace fakeit;
using namespace std::placeholders;

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
  auto content = Content::makeUnique();
  auto contentPtr = content.get();
  
  When(Method(messageQueue, addRequest)).Do([=](const Request& request) {
    REQUIRE(request.getRequestType() == "get");
    REQUIRE(request.getSender() == "clientId");
    REQUIRE(request.getResource() == "resource");
    REQUIRE(request.getContent() == contentPtr);
    return Status::OK;
  });

  FakeMessageQueue mq(messageQueue.get());
  auto client = QueueGenericClient::makeUnique("clientId", mq);
  client->sendRequest("get", "resource", std::move(content));

  Verify(Method(messageQueue, addRequest));
}

TEST_CASE("queue generic client can process a response", "[QueueGenericClient]") {
  Mock<IMessageQueue> messageQueue;
  auto client = QueueGenericClient::makeUnique("id", messageQueue.get());
  auto content = Status::makeUnique(Status::OK);
  auto contentPtr = content.get();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onResponse)).Do([=](const Response& response) {
    REQUIRE(response.getRequestType() == "get");
    REQUIRE(response.getReceiver() == "receiver");
    REQUIRE(response.getResource() == "resource");
    REQUIRE(&response.getContent() == contentPtr);
    return Status::OK;
  });

  client->setOnResponse(std::bind(&EventSink::onResponse, &eventSink.get(), _1));

  Response response("receiver", "get", "resource", std::move(content));
  client->onResponse(response);

  Verify(Method(eventSink, onResponse));
}

TEST_CASE("queue generic client can process an event", "[QueueGenericClient]") {
  Mock<IMessageQueue> messageQueue;
  auto client = QueueGenericClient::makeShared("id", messageQueue.get());
  auto content = Content::makeUnique();
  auto contentPtr = content.get();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onEvent)).Do([=](const Event& event) {
    REQUIRE(event.getEventType() == "created");
    REQUIRE(event.getResource() == "resource");
    REQUIRE(event.getContent() == contentPtr);
    return Status::OK;
  });

  client->setOnEvent(std::bind(&EventSink::onEvent, &eventSink.get(), _1));

  Event event("created", "resource", std::move(content));
  client->onEvent(event);

  Verify(Method(eventSink, onEvent));
}
