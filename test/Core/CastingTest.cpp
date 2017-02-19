#include "Utils/Testing.hpp" 

#include "Core/IEntity.hpp"
#include "Core/Casting.hpp"

using namespace Core;

namespace {

  class BaseClass : public IEntity {
	  TYPE_INFO(BaseClass, IEntity, "base")
  };

  class DerivedClass : public BaseClass {
	  TYPE_INFO(DerivedClass, BaseClass, "derived")
  };

}

TEST_CASE("successful casting", "[Casting]") {

	SECTION("unique to unique casting succeeds") {
		std::unique_ptr<BaseClass> base = makeUnique<DerivedClass>();
		auto basePtr = base.get();
		auto derived = castToUnique<DerivedClass>(std::move(base));
		REQUIRE(base.get() == nullptr);
		REQUIRE(derived.get() == basePtr);
	}

	SECTION("unique to shared casting succeeds") {
		std::unique_ptr<BaseClass> base = makeUnique<DerivedClass>();
		auto basePtr = base.get();
		auto derived = castToShared<DerivedClass>(std::move(base));
		REQUIRE(base.get() == nullptr);
		REQUIRE(derived.get() == basePtr);
	}

	SECTION("shared to shared casting succeeds") {
		std::shared_ptr<BaseClass> base = std::make_shared<DerivedClass>();
		auto derived = castToShared<DerivedClass>(base);
		REQUIRE(base.get() == base.get());
	}

}

TEST_CASE("unsuccessful casting", "[Casting]") {

	SECTION("unique to unique casting fails") {
		auto base = makeUnique<BaseClass>();
		auto derived = castToUnique<DerivedClass>(std::move(base));
		REQUIRE(base.get() != nullptr);
		REQUIRE(derived.get() == nullptr);
	}

	SECTION("unique to shared casting fails") {
		auto base = makeUnique<BaseClass>();
		auto derived = castToShared<DerivedClass>(std::move(base));
		REQUIRE(base.get() != nullptr);
		REQUIRE(derived.get() == nullptr);
	}

	SECTION("shared to shared casting fails") {
		auto base = std::make_shared<BaseClass>();
		auto derived = castToShared<DerivedClass>(base);
		REQUIRE(base.get() != nullptr);
		REQUIRE(derived.get() == nullptr);
	}

}