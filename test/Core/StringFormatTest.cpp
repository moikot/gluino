#include "Catch/catch.hpp"

#include "Core/StringFormat.hpp"

TEST_CASE("String is formatted", "[toString]")
{
	SECTION("int")
	{
		auto s = Core::toString((int)10);
		REQUIRE(s == "10");
	}
}
