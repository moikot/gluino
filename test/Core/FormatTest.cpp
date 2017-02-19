#include "Utils/Testing.hpp" 

#include "Core/Format.hpp"

using namespace Core;

TEST_CASE("format IP", "[Format]") {
  auto str = ipToString(0x01020304);
  REQUIRE(str == "1.2.3.4");
}

TEST_CASE("format int", "[Format]") {
  auto str = toString(static_cast<int>(100));
  REQUIRE(str == "100");
}

TEST_CASE("format unsigned", "[Format]") {
  auto str = toString(static_cast<unsigned>(100));
  REQUIRE(str == "100");
}

TEST_CASE("format long", "[Format]") {
  auto str = toString(static_cast<long>(100));
   REQUIRE(str == "100");
}

TEST_CASE("format unsigned long", "[Format]") {
  auto str = toString(static_cast<unsigned long>(100));
  REQUIRE(str == "100");
}

TEST_CASE("format long long", "[Format]") {
  auto str = toString(static_cast<long long>(100));
  REQUIRE(str == "100");
}

TEST_CASE("format unsigned long long", "[Format]") {
  auto str = toString(static_cast<unsigned long long>(100));
  REQUIRE(str == "100");
}

TEST_CASE("format float", "[Format]") {
  auto str = toString(static_cast<float>(100.5));
  REQUIRE(str == "100.500000");
}

TEST_CASE("format double", "[Format]") {
  auto str = toString(static_cast<double>(100.1));
  REQUIRE(str == "100.100000");
}

TEST_CASE("format long double", "[Format]") {
  auto str = toString(static_cast<long double>(100.1));
  REQUIRE(str == "100.100000");
}