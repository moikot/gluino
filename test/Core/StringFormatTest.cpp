#include "Catch/catch.hpp"

#include "Core/StringFormat.hpp"

using namespace Core;

TEST_CASE("String is formatted", "[toString]")
{
	SECTION("int")
	{
		auto s = toString((int)10);
		REQUIRE(s == "10");
	}
	SECTION("float")
	{
		auto s = toString((float)10.2);
		REQUIRE(s == "10.200000");
	}
}
