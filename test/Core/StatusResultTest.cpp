
#include "Catch/catch.hpp"

#include "Core/StatusResult.hpp"

using namespace Core;

TEST_CASE("StatusResult is created", "[StatusResult]")
{
	SECTION("Status code is retained")
	{
    auto result = StatusResult::makeUnique(StatusCode::OK, "test");
		REQUIRE(result->getStatusCode() == StatusCode::OK);
	}
	SECTION("Message is retainer")
	{
    auto result = StatusResult::makeUnique(StatusCode::OK, "test");
    REQUIRE(result->getMessage() == "test");
	}
}
