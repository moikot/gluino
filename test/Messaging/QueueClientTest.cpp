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
    virtual void onNotification(const Notification&) const = 0;
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

  When(Method(messageQueue, sendMessage)).Do([=](Message::Shared message) {
    auto request = castToShared<Request>(message);

    REQUIRE(request->getSender() == "id");
    REQUIRE(request->getReceiver() == "");
    REQUIRE(request->getActionType() == ActionType::Get);
    REQUIRE(request->getResource() == "resource");
    REQUIRE(request->getContent() == contentPtr);
    return StatusResult::OK(); 
  });

  auto client = QueueClient::makeUnique("id", messageQueue.get());
  client->sendRequest(ActionType::Get, "resource", std::move(content));

  Verify(Method(messageQueue, sendMessage));
}

TEST_CASE("responce handler is invoked", "[QueueClient]") {

  Mock<IMessageQueue> messageQueue;
  auto client = QueueClient::makeUnique("id", messageQueue.get());
  auto result = StatusResult::OK();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onResponse)).Do([=](const Response& response) {
    REQUIRE(response.getSender() == "sender");
    REQUIRE(response.getReceiver() == "receiver");
    REQUIRE(response.getActionType() == ActionType::Get);
    REQUIRE(response.getResource() == "resource");
    REQUIRE(response.getResult().getStatusCode() == StatusCode::OK);
    return StatusResult::OK();
  });

  client->setOnResponse(std::bind(&EventSink::onResponse, &eventSink.get(), _1));

  Response response("sender", "receiver", ActionType::Get, "resource", std::move(result));
  client->onResponse(response);

  Verify(Method(eventSink, onResponse));
  
}

TEST_CASE("notification handler is invoked", "[QueueClient]") {

  Mock<IMessageQueue> messageQueue;
  auto client = QueueClient::makeUnique("id", messageQueue.get());
  auto content = Content::makeShared();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onNotification)).Do([=](const Notification& notification) {
    REQUIRE(notification.getSender() == "sender");
    REQUIRE(notification.getReceiver() == "receiver");
    REQUIRE(notification.getActionType() == ActionType::Get);
    REQUIRE(notification.getResource() == "resource");
    REQUIRE(notification.getContent() == content.get());
    return StatusResult::OK();
  });

  client->setOnNotification(std::bind(&EventSink::onNotification, &eventSink.get(), _1));

  Notification notification("sender", "receiver", ActionType::Get, "resource", content);
  client->onNotification(notification);

  Verify(Method(eventSink, onNotification));

}