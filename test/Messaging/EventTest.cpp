#include "catch.hpp"

#include "Messaging/Event.hpp"

using namespace Messaging;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

  Event::Unique createEvent(Core::IEntity::Shared content) {
    return Event::makeUnique("sender", ActionType::Get, "resource", content);
  }

}

TEST_CASE("Event can be constructed", "[Event]") {

  auto event = createEvent(nullptr);

  SECTION("sender retained") {
    REQUIRE(event->getSender()  == "sender");
  }

  SECTION("action type retained") {
    REQUIRE(event->getActionType() == ActionType::Get);
  }

  SECTION("resource retained") {
    REQUIRE(event->getResource() == "resource");
  }

  SECTION("content retained") {
    auto content = Content::makeShared();
    auto event = createEvent(content);
    REQUIRE(event->getContent() == content.get());
  }

}
