#include "Utils/Testing.hpp" 

#include "Messaging/Request.hpp"

using namespace Core;
using namespace Messaging;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

}

TEST_CASE("Request can be constructed", "[Request]") {
	auto content = Content::makeUnique();
	auto contentPtr = content.get();

	auto requestNoContent = Request::makeUnique("sender", "get", "resource");
	auto requestWithContent = Request::makeUnique("sender", "get", "resource", std::move(content));

	SECTION("type is correct") {
		REQUIRE(requestNoContent->getTypeId() == "request");
		REQUIRE(requestWithContent->getTypeId() == "request");
	}

	SECTION("sender retained") {
		REQUIRE(requestNoContent->getSender() == "sender");
		REQUIRE(requestWithContent->getSender() == "sender");
	}

	SECTION("requestWithContent type retained") {
		REQUIRE(requestNoContent->getRequestType() == "get");
		REQUIRE(requestWithContent->getRequestType() == "get");
	}

	SECTION("resource retained") {
		REQUIRE(requestNoContent->getResource() == "resource");
		REQUIRE(requestWithContent->getResource() == "resource");
	}

	SECTION("result retained") {
		REQUIRE(requestNoContent->getContent() == nullptr);
		REQUIRE(requestWithContent->getContent() == contentPtr);
	}

	SECTION("based on another request with the sender replaced") {
		auto newRequest = Request::makeUnique("new_sender", std::move(*requestWithContent));
		REQUIRE(newRequest->getSender() == "new_sender");
		REQUIRE(newRequest->getRequestType() == "get");
		REQUIRE(newRequest->getResource() == "resource");

		// Content moved
		REQUIRE(newRequest->getContent() == contentPtr);
		REQUIRE(requestWithContent->getContent() == nullptr);
	}
}
