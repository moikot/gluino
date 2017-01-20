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
    virtual Core::IEntity::Unique onRequest(const Content&) = 0;
  };

}

TEST_CASE("queue resource controller can send an event", "[QueueResourceController]") {
  Mock<IMessageQueue> messageQueue;
  auto content = Content::makeUnique();
  auto contentPtr = content.get();

  When(Method(messageQueue, addEvent)).Do([=](Event::Shared request) {
    REQUIRE(request->getEventType() == "created");
    REQUIRE(request->getResource() == "resource");
    REQUIRE(request->getContent() == contentPtr);
    return Status::OK();
  });

  auto client = QueueResourceController::makeUnique("resource", messageQueue.get());
  client->sendEvent("created", std::move(content));

  Verify(Method(messageQueue, addEvent));
}

TEST_CASE("queue resource controller can process a request", "[QueueResourceController]") {
  Mock<IMessageQueue> messageQueue;
  auto client = QueueResourceController::makeUnique("resource", messageQueue.get());
  auto content = Content::makeShared();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onRequest)).Do([=](const Content& param) {
    REQUIRE(&param == content.get());
    return Status::OK();
  });
  client->addOnRequest<Content>("create", std::bind(&EventSink::onRequest, &eventSink.get(), _1));

  Request request("create", "sender", "resource", content);
  auto handler = client->getRequestHandler(request);
  REQUIRE(handler != nullptr);

  auto response = handler(request);
  REQUIRE(response != nullptr);

  Verify(Method(eventSink, onRequest));
}
