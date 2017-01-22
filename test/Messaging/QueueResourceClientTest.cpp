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
    virtual void onResponse(const Status&) = 0;
    virtual void onEvent(const Content&) const = 0;
  };

}

TEST_CASE("queue resource client can send a request", "[QueueResourceClient]") {
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

  auto client = QueueResourceClient::makeUnique("clientId", "resource", messageQueue.get());
  client->sendRequest("get", std::move(content));

  Verify(Method(messageQueue, addRequest));
}

TEST_CASE("queue resource client can process a response", "[QueueResourceClient]") {
  Mock<IMessageQueue> messageQueue;
  auto client = QueueResourceClient::makeUnique("id", "resource", messageQueue.get());
  auto result = Status::makeUnique(Status::OK);
  auto resultPtr = result.get();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onResponse)).Do([=](const Status& result) {
    REQUIRE(&result == resultPtr);
    return Status::OK;
  });
  client->addOnResponse<Status>("get", std::bind(&EventSink::onResponse, &eventSink.get(), _1));

  Response response("get", "receiver", "resource", std::move(result));
  client->onResponse(response);

  Verify(Method(eventSink, onResponse));
}

TEST_CASE("queue resource client can process an event", "[QueueResourceClient]") {
  Mock<IMessageQueue> messageQueue;
  auto client = QueueResourceClient::makeUnique("id", "resource", messageQueue.get());
  auto content = Content::makeShared();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onEvent)).Do([=](const Content& param) {
    REQUIRE(&param == content.get());
    return Status::OK;
  });
  client->addOnEvent<Content>("created", std::bind(&EventSink::onEvent, &eventSink.get(), _1));

  Event event("created", "resource", content);
  client->onEvent(event);

  Verify(Method(eventSink, onEvent));
}
