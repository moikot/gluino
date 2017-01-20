#include "Utils/Testing.hpp" 

#include "Messaging/MessageQueue.hpp"

using namespace Core;
using namespace Messaging;

using namespace fakeit;
using namespace std::placeholders;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

  struct EventSink {
    virtual Core::IEntity::Unique onRequest(const Content&) = 0;
    virtual void onResponse(const Response&) = 0;
    virtual void onResponseContent(const Content&) = 0;
    virtual void onEvent(const Event&) const = 0;
    virtual void onEventContent(const Content&) const = 0;
  };

}

TEST_CASE("message queue is routing an event to a generic client", "[MessageQueue]") {
  auto content = Content::makeShared();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onEvent)).Do([=](const Event& event) {
    REQUIRE(event.getEventType() == "created");
    REQUIRE(event.getResource() == "resource");
    REQUIRE(event.getContent() == content.get());
    return Status::OK();
  });

  auto queue = MessageQueue::makeUnique();

  auto client = queue->createGenericClient("clientId");
  client->setOnEvent(std::bind(&EventSink::onEvent, &eventSink.get(), _1));

  auto event = Event::makeShared("created", "resource", content);
  queue->addEvent(event);
  queue->idle();

  Verify(Method(eventSink, onEvent));
}

TEST_CASE("message queue is routing a response to a generic client", "[MessageQueue]") {
  auto requestContent = Content::makeShared();
  auto responseContent = Content::makeUnique();
  auto responseContentPtr = responseContent.get();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onRequest)).Do([&](const Content& param) {
    REQUIRE(&param == requestContent.get());
    return std::move(responseContent);
  });

  When(Method(eventSink, onResponse)).Do([=](const Response& response) {
    REQUIRE(response.getRequestType() == "get");
    REQUIRE(response.getReceiver() == "clientId");
    REQUIRE(response.getResource() == "resource");
    REQUIRE(&response.getContent() == responseContentPtr);
    return Status::OK();
  });

  auto queue = MessageQueue::makeUnique();

  auto client = queue->createGenericClient("clientId");
  client->setOnResponse(std::bind(&EventSink::onResponse, &eventSink.get(), _1));

  auto controller = queue->createResourceController("resource");
  controller->addOnRequest<Content>("get", std::bind(&EventSink::onRequest, &eventSink.get(), _1));

  client->sendRequest("get", "resource", requestContent);
  queue->idle();

  Verify(Method(eventSink, onRequest));
  Verify(Method(eventSink, onResponse));
}

TEST_CASE("message queue is routing an event to a resource client", "[MessageQueue]") {
  auto content = Content::makeShared();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onEventContent)).Do([=](const Content& param) {
    REQUIRE(&param == content.get());
    return Status::OK();
  });

  auto queue = MessageQueue::makeUnique();

  auto client = queue->createResourceClient("clientId", "resource");
  client->addOnEvent<Content>("created", std::bind(&EventSink::onEventContent, &eventSink.get(), _1));

  auto event = Event::makeShared("created", "resource", content);
  queue->addEvent(event);
  queue->idle();

  Verify(Method(eventSink, onEventContent));
}

TEST_CASE("message queue is routing a response to a resource client", "[MessageQueue]") {
  auto requestContent = Content::makeShared();
  auto responseContent = Content::makeUnique();
  auto responseContentPtr = responseContent.get();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onRequest)).Do([&](const Content& param) {
    REQUIRE(&param == requestContent.get());
    return std::move(responseContent);
  });

  When(Method(eventSink, onResponseContent)).Do([=](const Content& param) {
    REQUIRE(&param == responseContentPtr);
    return Status::OK();
  });

  auto queue = MessageQueue::makeUnique();

  auto client = queue->createResourceClient("clientId", "resource");
  client->addOnResponse<Content>("get", std::bind(&EventSink::onResponseContent, &eventSink.get(), _1));

  auto controller = queue->createResourceController("resource");
  controller->addOnRequest<Content>("get", std::bind(&EventSink::onRequest, &eventSink.get(), _1));

  client->sendRequest("get", requestContent);
  queue->idle();

  Verify(Method(eventSink, onRequest));
  Verify(Method(eventSink, onResponseContent));
}
