#include "catch.hpp" 

#include "Core/ObjectResult.hpp"

using namespace Core;

namespace {

  class ObjectClass : public IEntity {
    TYPE_INFO(ObjectClass, IEntity, "base")
  };

}

TEST_CASE("ObjectResult can be constructed", "[ObjectResult]") {
  
  auto obj = ObjectClass::makeUnique();
  auto objPtr = obj.get();
  auto result = ObjectResult::makeUnique(StatusCode::OK, std::move(obj));

  SECTION("status code retained") {
    REQUIRE(result->getStatusCode() == StatusCode::OK);
  }

  SECTION("object retained") {
    REQUIRE(&result->getObject() == objPtr);
  }

}
