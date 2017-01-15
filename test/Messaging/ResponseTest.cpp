#include "catch.hpp"

#include "Core/StatusResult.hpp"
#include "Messaging/Response.hpp"

using namespace Core;
using namespace Messaging;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

  Response::Unique createResponse(Core::IEntity::Shared content) {
    return Response::makeUnique("get", "sender", "receiver", "resource", content);
  }

}

TEST_CASE("Response can be constructed", "[Response]") {

  auto content = Content::makeShared();
  auto response = createResponse(content);

  SECTION("type is correct") {
    REQUIRE(response->getTypeId() == "response");
  }

  SECTION("request type retained") {
    REQUIRE(response->getRequestType() == "get");
  }

  SECTION("sender retained") {
    REQUIRE(response->getSender() == "sender");
  }

  SECTION("receiver retained") {
    REQUIRE(response->getReceiver() == "receiver");
  }

  SECTION("resource retained") {
    REQUIRE(response->getResource() == "resource");
  }

  SECTION("content retained") {
    REQUIRE(&response->getContent() == content.get());
  }

}
