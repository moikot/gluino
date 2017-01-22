#include "Utils/Testing.hpp" 

#include "Messaging/IMessageQueue.hpp"

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
  Mock<IMessageQueue> messageQueue;
  auto content = Content::makeUnique();
  auto contentPtr = content.get();

  When(Method(messageQueue, addRequest)).Do([=](Request::Shared request) {
    REQUIRE(request->getRequestType() == "get");
    REQUIRE(request->getSender() == "clientId");
    REQUIRE(request->getResource() == "resource");
    REQUIRE(request->getContent() == contentPtr);
    return Status::OK;
  });

  auto client = QueueGenericClient::makeUnique("clientId", messageQueue.get());
  client->sendRequest("get", "resource", std::move(content));

  Verify(Method(messageQueue, addRequest));
}

TEST_CASE("queue generic client can process a response", "[QueueGenericClient]") {
  Mock<IMessageQueue> messageQueue;
  auto client = QueueGenericClient::makeUnique("id", messageQueue.get());
  auto result = Status::makeShared(Status::OK);
  auto resultPtr = result.get();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onResponse)).Do([=](const Response& response) {
    REQUIRE(response.getRequestType() == "get");
    REQUIRE(response.getReceiver() == "receiver");
    REQUIRE(response.getResource() == "resource");
    REQUIRE(&response.getContent() == resultPtr);
    return Status::OK;
  });

  client->setOnResponse(std::bind(&EventSink::onResponse, &eventSink.get(), _1));

  Response response("get", "receiver", "resource", std::move(result));
  client->onResponse(response);

  Verify(Method(eventSink, onResponse));
}

TEST_CASE("queue generic client can process an event", "[QueueGenericClient]") {
  Mock<IMessageQueue> messageQueue;
  auto client = QueueGenericClient::makeUnique("id", messageQueue.get());
  auto content = Content::makeShared();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onEvent)).Do([=](const Event& event) {
    REQUIRE(event.getEventType() == "created");
    REQUIRE(event.getResource() == "resource");
    REQUIRE(event.getContent() == content.get());
    return Status::OK;
  });

  client->setOnEvent(std::bind(&EventSink::onEvent, &eventSink.get(), _1));

  Event event("created", "resource", content);
  client->onEvent(event);

  Verify(Method(eventSink, onEvent));
}
