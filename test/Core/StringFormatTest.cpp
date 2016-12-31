#include "Catch/catch.hpp"

#include "Core/StringFormat.hpp"

TEST_CASE("String is formatted", "[toString]")
{
	SECTION("int")
	{
		auto s = Core::toString((int)10);
		REQUIRE(s == "10");
	}
	SECTION("float")
	{
		auto s = Core::toString((float)10.2);
		REQUIRE(s == "10.200000");
	}
}
