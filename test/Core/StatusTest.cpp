#include "Utils/Testing.hpp"

#include "Core/Status.hpp"

using namespace Core;

TEST_CASE("static creators", "[Status]") {
  SECTION("OK status result has OK status code") {
    REQUIRE(Status::OK.getStatusCode() == StatusCode::OK);
  }
  SECTION("NotImplemented status result has NotImplemented status code") {
    REQUIRE(Status::NotImplemented.getStatusCode() == StatusCode::NotImplemented);
  }
}

TEST_CASE("Status can be constructed", "[Status]") {

  auto status = Status(StatusCode::OK, "test");

  SECTION("status code retained") {
    REQUIRE(status.getStatusCode() == StatusCode::OK);
  }
  SECTION("message retained") {
    REQUIRE(status.getMessage() == "test");
  }
  SECTION("inner result is null by default") {
    REQUIRE(status.getInnerStatus() == nullptr);
  }
  SECTION("inner result is retained") {
    auto outer = Status(StatusCode::NotFound, "test", status);
    REQUIRE(outer.getInnerStatus()->getStatusCode() == StatusCode::OK);
  }
}

TEST_CASE("Status isOK method", "[Status]") {
  SECTION("is OK when status code is OK") {
    auto result = Status(StatusCode::OK, "test");
    REQUIRE(result.isOk());
  }
  SECTION("is not OK when status code is not OK") {
    auto result = Status(StatusCode::Accepted, "test");
    REQUIRE(!result.isOk());
  }
}
