#include "Utils/Testing.hpp" 

#include "Messaging/Event.hpp"

using namespace Messaging;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

  Event::Unique createEvent(Core::IEntity::Shared content) {
    return Event::makeUnique("created", "resource", content);
  }

}

TEST_CASE("Event can be constructed", "[Event]") {

  auto content = Content::makeShared();
  auto event = createEvent(content);

  SECTION("type is correct") {
    REQUIRE(event->getTypeId() == "event");
  }

  SECTION("event type retained") {
    REQUIRE(event->getEventType() == "created");
  }

  SECTION("resource retained") {
    REQUIRE(event->getResource() == "resource");
  }

  SECTION("content retained") {
    REQUIRE(event->getContent() == content.get());
  }

}
