#include "catch.hpp"

#include "Messaging/Request.hpp"

using namespace Core;
using namespace Messaging;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

  Request::Unique createRequest(IEntity::Shared content) {
    return Request::makeUnique("get", "sender", "resource", content);
  }

}

TEST_CASE("Request can be constructed", "[Request]") {

  auto content = Content::makeShared();
  auto request = createRequest(content);

  SECTION("request type retained") {
    REQUIRE(request->getRequestType() == "get");
  }

  SECTION("sender retained") {
    REQUIRE(request->getSender() == "sender");
  }

  SECTION("resource retained") {
    REQUIRE(request->getResource() == "resource");
  }

  SECTION("result retained") {
    REQUIRE(request->getContent() == content.get());
  }

}
