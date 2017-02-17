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
    virtual void onResponseStatus(const Status&) = 0;
    virtual void onEvent(const Event&) const = 0;
    virtual void onEventContent(const Content&) const = 0;
  };

}

TEST_CASE("message queue is routing an event to a generic client", "[MessageQueue]") {
  auto content = Content::makeUnique();
  auto contentPtr = content.get();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onEvent)).Do([=](const Event& event) {
    REQUIRE(event.getEventType() == "created");
    REQUIRE(event.getResource() == "resource");
    REQUIRE(event.getContent() == contentPtr);
    return Status::OK;
  });

  Mock<ILogger> loggerInstanse;
  Fake(Method(loggerInstanse, message));
  auto logger = ILogger::Shared(&loggerInstanse.get(), [](...) {});

  auto queue = MessageQueue::makeUnique(*logger);

  auto client = queue->createClient("clientId");
  client->setOnEvent(std::bind(&EventSink::onEvent, &eventSink.get(), _1));

  auto event = Event::makeUnique("created", "resource", std::move(content));
  queue->addEvent(std::move(event));
  queue->idle();

  Verify(Method(eventSink, onEvent));
}

TEST_CASE("message queue is not routing an event to a deleted generic client", "[MessageQueue]") {
  Mock<ILogger> loggerInstanse;
  Fake(Method(loggerInstanse, message));

  auto logger = ILogger::Shared(&loggerInstanse.get(), [](...) {});
  auto queue = MessageQueue::makeUnique(*logger);

  {
    Mock<EventSink> eventSink;
    auto client = queue->createClient("clientId");
    client->setOnEvent(std::bind(&EventSink::onEvent, &eventSink.get(), _1));
    client.reset();
  }

  queue->addEvent(Event::makeUnique("created", "resource"));
  queue->idle();
}

TEST_CASE("message queue is routing a response to a generic client", "[MessageQueue]") {
  auto requestContent = Content::makeUnique();
  auto requestContentPtr = requestContent.get();
  auto responseContent = Content::makeUnique();
  auto responseContentPtr = responseContent.get();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onRequest)).Do([&](const Content& param) {
    REQUIRE(&param == requestContentPtr);
    return std::move(responseContent);
  });

  When(Method(eventSink, onResponse)).Do([=](const Response& response) {
    REQUIRE(response.getRequestType() == "get");
    REQUIRE(response.getReceiver() == "clientId");
    REQUIRE(response.getResource() == "resource");
    REQUIRE(&response.getContent() == responseContentPtr);
    return Status::OK;
  });

  Mock<ILogger> loggerInstanse;
  Fake(Method(loggerInstanse, message));
  auto logger = ILogger::Shared(&loggerInstanse.get(), [](...) {});

  auto queue = MessageQueue::makeUnique(*logger);

  auto client = queue->createClient("clientId");
  client->setOnResponse(std::bind(&EventSink::onResponse, &eventSink.get(), _1));

  queue->createController("resource_controller_before");
  auto controller = queue->createController("resource");
  queue->createController("resource_controller_after");

  controller->addOnRequest("get", [&](const Content& c){ return eventSink.get().onRequest(c); });

  client->sendRequest("get", "resource", std::move(requestContent));
  queue->idle();

  Verify(Method(eventSink, onRequest));
  Verify(Method(eventSink, onResponse));
}


TEST_CASE("message queue is routing an event to a resource client", "[MessageQueue]") {
  auto content = Content::makeUnique();
  auto contentPtr = content.get();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onEventContent)).Do([=](const Content& param) {
    REQUIRE(&param == contentPtr);
    return Status::OK;
  });

  Mock<ILogger> loggerInstanse;
  Fake(Method(loggerInstanse, message));
  auto logger = ILogger::Shared(&loggerInstanse.get(), [](...) {});

  auto queue = MessageQueue::makeUnique(*logger);

  auto client = queue->createClient("clientId", "resource");
  client->addOnEvent("created", [&](const Content& c){ eventSink.get().onEventContent(c); });

  auto event = Event::makeUnique("created", "resource", std::move(content));
  queue->addEvent(std::move(event));
  queue->idle();

  Verify(Method(eventSink, onEventContent));
}

TEST_CASE("message queue is routing a response to a resource client", "[MessageQueue]") {
  auto requestContent = Content::makeUnique();
  auto requestContentPtr = requestContent.get();
  auto responseContent = Content::makeUnique();
  auto responseContentPtr = responseContent.get();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onRequest)).Do([&](const Content& param) {
    REQUIRE(&param == requestContentPtr);
    return std::move(responseContent);
  });

  When(Method(eventSink, onResponseContent)).Do([=](const Content& param) {
    REQUIRE(&param == responseContentPtr);
    return Status::OK;
  });

  Mock<ILogger> loggerInstanse;
  Fake(Method(loggerInstanse, message));
  auto logger = ILogger::Shared(&loggerInstanse.get(), [](...) {});

  auto queue = MessageQueue::makeUnique(*logger);

  auto client = queue->createClient("clientId", "resource");
  client->addOnResponse("get", [&](const Content& c){ return eventSink.get().onResponseContent(c); });

  queue->createController("resource_controller_before");
  auto controller = queue->createController("resource");
  queue->createController("resource_controller_after");
  controller->addOnRequest("get", [&](const Content& c){ return eventSink.get().onRequest(c); });

  client->sendRequest("get", std::move(requestContent));
  queue->idle();

  Verify(Method(eventSink, onRequest));
  Verify(Method(eventSink, onResponseContent));
}

TEST_CASE("message queue is failing to route a response to an explicitly deleted client", "[MessageQueue]") {
  auto requestContent = Content::makeUnique();
  auto responseContent = Content::makeUnique();

  Mock<EventSink> eventSink;
  When(Method(eventSink, onRequest)).Do([&](const Content&) {
    return std::move(responseContent);
  });

  Mock<ILogger> loggerInstanse;
  Fake(Method(loggerInstanse, message));
  Fake(Method(loggerInstanse, error));

  auto logger = ILogger::Shared(&loggerInstanse.get(), [](...) {});
  auto queue = MessageQueue::makeUnique(*logger);

  auto client = queue->createClient("clientId", "resource");
  auto controller = queue->createController("resource");
  controller->addOnRequest("get", [&](const Content& c) { return eventSink.get().onRequest(c); });

  client->sendRequest("get", std::move(requestContent));
  queue->removeClient(*client);
  queue->idle();

  Verify(Method(eventSink, onRequest));
  Verify(Method(loggerInstanse, message));
  Verify(Method(loggerInstanse, error));
}

TEST_CASE("message queue is failing to route a request if there is no controller to handle it", "[MessageQueue]") {
  auto requestContent = Content::makeUnique();

  Mock<EventSink> eventSink;

  When(Method(eventSink, onResponseStatus)).Do([=](const Status& status) {
    REQUIRE(status.getStatusCode() == StatusCode::NotFound);
    return Status::OK;
  });

  Mock<ILogger> loggerInstanse;
  Fake(Method(loggerInstanse, message));
  Fake(Method(loggerInstanse, error));
  auto logger = ILogger::Shared(&loggerInstanse.get(), [](...) {});

  auto queue = MessageQueue::makeUnique(*logger);

  auto client = queue->createClient("clientId", "resource");
  client->addOnResponse("get", [&](const Status& c){ return eventSink.get().onResponseStatus(c); });

  client->sendRequest("get", std::move(requestContent));
  queue->idle();

  Verify(Method(eventSink, onResponseStatus));
}

TEST_CASE("message queue is failing to route a request if the controller was explicitly deleted", "[MessageQueue]") {
  auto requestContent = Content::makeUnique();
  auto responseContent = Content::makeUnique();

  Mock<EventSink> eventSink;

  When(Method(eventSink, onResponseStatus)).Do([=](const Status& status) {
    REQUIRE(status.getStatusCode() == StatusCode::NotFound);
    return Status::OK;
  });

  Mock<ILogger> loggerInstanse;
  Fake(Method(loggerInstanse, message));
  Fake(Method(loggerInstanse, error));
  auto logger = ILogger::Shared(&loggerInstanse.get(), [](...) {});

  auto queue = MessageQueue::makeUnique(*logger);

  auto client = queue->createClient("clientId", "resource");
  client->addOnResponse("get", [&](const Status& c){ return eventSink.get().onResponseStatus(c); });
  auto controller = queue->createController("resource");

  client->sendRequest("get", std::move(requestContent));
  queue->removeController(*controller);
  queue->idle();

  Verify(Method(eventSink, onResponseStatus));
}
