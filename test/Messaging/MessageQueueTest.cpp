#include "catch.hpp"
#include "fakeit.hpp"

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
    virtual void onResponse(const Response&) = 0;
    virtual void onResponseStatus(const StatusResult&) = 0;
    virtual void onEvent(const Event&) const = 0;
    virtual void onEventContent(const Content&) const = 0;
  };

}

TEST_CASE("message queue is routing event to a generic client", "[MessageQueue]") {
  auto content = Content::makeShared();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onEvent)).Do([=](const Event& event) {
    REQUIRE(event.getEventType() == "created");
    REQUIRE(event.getResource() == "resource");
    REQUIRE(event.getContent() == content.get());
    return StatusResult::OK();
  });

  auto queue = MessageQueue::makeUnique();

  auto client = queue->createGenericClient("clientId");
  client->setOnEvent(std::bind(&EventSink::onEvent, &eventSink.get(), _1));

  auto event = Event::makeShared("created", "resource", content);
  queue->addEvent(event);
  queue->idle();

  Verify(Method(eventSink, onEvent));
}

TEST_CASE("message queue is routing event to a resource client", "[MessageQueue]") {
  auto content = Content::makeShared();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onEventContent)).Do([=](const Content& param) {
    REQUIRE(&param == content.get());
    return StatusResult::OK();
  });

  auto queue = MessageQueue::makeUnique();

  auto client = queue->createResourceClient("clientId", "resource");
  client->addOnEvent<Content>("created", std::bind(&EventSink::onEventContent, &eventSink.get(), _1));

  auto event = Event::makeShared("created", "resource", content);
  queue->addEvent(event);
  queue->idle();

  Verify(Method(eventSink, onEventContent));
}
