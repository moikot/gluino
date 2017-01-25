#include "Utils/Testing.hpp"

#include "Core/Status.hpp"
#include "Messaging/Response.hpp"

using namespace Core;
using namespace Messaging;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

}

TEST_CASE("Response can be constructed", "[Response]") {
  auto content = Content::makeUnique();
  auto contentPtr = content.get();

  auto response = Response::makeUnique("receiver", "get", "resource", std::move(content));

  SECTION("type is correct") {
    REQUIRE(response->getTypeId() == "response");
  }

  SECTION("receiver retained") {
	  REQUIRE(response->getReceiver() == "receiver");
  }

  SECTION("request type retained") {
    REQUIRE(response->getRequestType() == "get");
  }

  SECTION("resource retained") {
    REQUIRE(response->getResource() == "resource");
  }

  SECTION("content retained") {
    REQUIRE(&response->getContent() == contentPtr);
  }
}
