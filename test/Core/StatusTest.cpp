#include "Utils/Testing.hpp" 

#include "Core/Status.hpp"

using namespace Core;

TEST_CASE("static creators", "[Status]") {

  SECTION("OK status result has OK status code") {
    REQUIRE(Status::OK()->getStatusCode() == StatusCode::OK);
  }

  SECTION("NotImplemented status result has NotImplemented status code") {
    REQUIRE(Status::NotImplemented()->getStatusCode() == StatusCode::NotImplemented);
  }

}

TEST_CASE("Status can be constructed", "[Status]") {

  auto result = Status::makeUnique(StatusCode::OK, "test");

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
    auto outer = Status::makeUnique(StatusCode::OK, "test", std::move(result));
    REQUIRE(outer->getInnerReuslt() == innerPtr);
  }

}

TEST_CASE("Status isOK method", "[Status]") {

  SECTION("is OK when status code is OK") {
    auto result = Status::makeUnique(StatusCode::OK, "test");
    REQUIRE(result->isOk());
  }

  SECTION("is not OK when status code is not OK") {
    auto result = Status::makeUnique(StatusCode::Accepted, "test");
    REQUIRE(!result->isOk());
  }

}
