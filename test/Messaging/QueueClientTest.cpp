#include "catch.hpp"
#include "fakeit.hpp"

#include "Core/Casting.hpp"
#include "Messaging/QueueClient.hpp"
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

TEST_CASE("QueueClient can be constructed", "[QueueClient]") {

  Mock<IMessageQueue> messageQueue;
  auto client = QueueClient::makeUnique("id", messageQueue.get());

  SECTION("identifier retained") {
    REQUIRE(client->getId() == "id");
  }

}

TEST_CASE("resource request is sent", "[QueueClient]") {

  Mock<IMessageQueue> messageQueue;
  auto content = Content::makeUnique();
  auto contentPtr = content.get();

  When(Method(messageQueue, addRequest)).Do([=](Request::Shared request) {
    REQUIRE(request->getSender() == "id");
    REQUIRE(request->getActionType() == ActionType("get"));
    REQUIRE(request->getResource() == "resource");
    REQUIRE(request->getContent() == contentPtr);
    return StatusResult::OK();
  });

  auto client = QueueClient::makeUnique("id", messageQueue.get());
  client->sendRequest(ActionType("get"), "resource", std::move(content));

  Verify(Method(messageQueue, addRequest));
}

TEST_CASE("responce handler is invoked", "[QueueClient]") {

  Mock<IMessageQueue> messageQueue;
  auto client = QueueClient::makeUnique("id", messageQueue.get());
  auto result = StatusResult::OK();
  auto resultPtr = result.get();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onResponse)).Do([=](const Response& response) {
    REQUIRE(response.getSender() == "sender");
    REQUIRE(response.getReceiver() == "receiver");
    REQUIRE(response.getActionType() == ActionType("get"));
    REQUIRE(response.getResource() == "resource");
    REQUIRE(&response.getContent() == resultPtr);
    return StatusResult::OK();
  });

  client->setOnResponse(std::bind(&EventSink::onResponse, &eventSink.get(), _1));

  Response response("sender", "receiver", ActionType("get"), "resource", std::move(result));
  client->onResponse(response);

  Verify(Method(eventSink, onResponse));

}

TEST_CASE("event handler is invoked", "[QueueClient]") {

  Mock<IMessageQueue> messageQueue;
  auto client = QueueClient::makeUnique("id", messageQueue.get());
  auto content = Content::makeShared();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onEvent)).Do([=](const Event& event) {
    REQUIRE(event.getSender() == "sender");
    REQUIRE(event.getActionType() == ActionType("get"));
    REQUIRE(event.getResource() == "resource");
    REQUIRE(event.getContent() == content.get());
    return StatusResult::OK();
  });

  client->setOnEvent(std::bind(&EventSink::onEvent, &eventSink.get(), _1));

  Event event("sender", ActionType("get"), "resource", content);
  client->onEvent(event);

  Verify(Method(eventSink, onEvent));

}
