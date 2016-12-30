#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <fstream>
#include <string>

TEST_CASE("Test", "[file]")
{
	SECTION("output is to a file")
	{
		REQUIRE(true);
	}
}
