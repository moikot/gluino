#include <gtest/gtest.h>

#include "Core/IEntity.hpp"
#include "Core/Memory.hpp"
#include "Core/Casting.hpp"

using namespace Core;

namespace {

class BaseClass : public IEntity {
  TYPE_INFO(BaseClass, IEntity, "BaseClass")
};

class DerivedClass : public BaseClass {
  TYPE_INFO(DerivedClass, BaseClass, "DerivedClass")
};

}

TEST(Casting, Unique_To_Unique_Succeeds) {
  BaseClass::Unique base = DerivedClass::makeUnique();
  auto basePtr = base.get();
  auto derived = castToUnique<DerivedClass>(std::move(base));
  ASSERT_EQ(base.get(), nullptr);
  ASSERT_EQ(derived.get(), basePtr);
}

TEST(Casting, Unique_To_Unique_Fails) {
  auto base = BaseClass::makeUnique();
  auto derived = castToUnique<DerivedClass>(std::move(base));
  ASSERT_NE(base.get(), nullptr);
  ASSERT_EQ(derived.get(), nullptr);
}

TEST(Casting, Unique_To_Shared_Succeeds) {
  BaseClass::Unique base = DerivedClass::makeUnique();
  auto basePtr = base.get();
  auto derived = castToShared<DerivedClass>(std::move(base));
  ASSERT_EQ(base.get(), nullptr);
  ASSERT_EQ(derived.get(), basePtr);
}

TEST(Casting, Unique_To_Shared_Fails) {
  auto base = BaseClass::makeUnique();
  auto derived = castToShared<DerivedClass>(std::move(base));
  ASSERT_NE(base.get(), nullptr);
  ASSERT_EQ(derived.get(), nullptr);
}

TEST(Casting, Shared_To_Shared_Succeeds) {
  BaseClass::Shared base = DerivedClass::makeShared();
  auto derived = castToShared<DerivedClass>(base);
  ASSERT_EQ(derived.get(), base.get());
}

TEST(Casting, Shared_To_Shared_Fails) {
  auto base = BaseClass::makeShared();
  auto derived = castToShared<DerivedClass>(base);
  ASSERT_NE(base.get(), nullptr);
  ASSERT_EQ(derived.get(), nullptr);
}
