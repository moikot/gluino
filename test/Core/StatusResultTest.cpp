#include "catch.hpp" 

#include "Core/StatusResult.hpp"

using namespace Core;

TEST_CASE("static creators", "[StatusResult]") {

  SECTION("OK status result has OK status code") {
    REQUIRE(StatusResult::OK()->getStatusCode() == StatusCode::OK);
  }

  SECTION("NotImplemented status result has NotImplemented status code") {
    REQUIRE(StatusResult::NotImplemented()->getStatusCode() == StatusCode::NotImplemented);
  }

}

TEST_CASE("StatusResult can be constructed", "[StatusResult]") {
  
  auto result = StatusResult::makeUnique(StatusCode::OK, "test");

  SECTION("status code retained") {
    REQUIRE(result->getStatusCode() == StatusCode::OK);
  }

  SECTION("message retained") {
    REQUIRE(result->getMessage() == "test");
  }

  SECTION("inner result is null by default") {
    REQUIRE(result->getInnerReuslt() == nullptr);
  }

  SECTION("inner result is retained") {
    auto innerPtr = result.get();
    auto outer = StatusResult::makeUnique(StatusCode::OK, "test", std::move(result));
    REQUIRE(outer->getInnerReuslt() == innerPtr);
  }

}

TEST_CASE("StatusResult isOK method", "[StatusResult]") {
  
  SECTION("is OK when status code is OK") {
    auto result = StatusResult::makeUnique(StatusCode::OK, "test");
    REQUIRE(result->isOk());
  }

  SECTION("is not OK when status code is not OK") {
    auto result = StatusResult::makeUnique(StatusCode::Accepted, "test");
    REQUIRE(!result->isOk());
  }

}

TEST_CASE("StatusResult isAccepted method", "[StatusResult]") {

  SECTION("is accepted when status code is Accepted") {
    auto result = StatusResult::makeUnique(StatusCode::Accepted, "test");
    REQUIRE(result->isAccepted());
  }

  SECTION("is not accepted when status code is not Accepted") {
    auto result = StatusResult::makeUnique(StatusCode::OK, "test");
    REQUIRE(!result->isAccepted());
  }

}
