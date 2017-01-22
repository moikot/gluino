#include "Utils/Testing.hpp"

#include "Serialization/StatusSerializer.hpp"

using namespace Core;
using namespace Serialization;

using namespace fakeit;
using namespace std::placeholders;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

}

TEST_CASE("can serialize a status", "[StatusSerializer]") {
  auto innerStatus = Status::NotImplemented;
  auto status = Status::makeUnique(StatusCode::InternalServerError, "serverError", innerStatus);

  Mock<ISerializationContext> context;

  When(Method(context, setInt).Using("code", (int)StatusCode::InternalServerError)).Do([](const std::string&, int) {
    return Status::OK;
  });

  When(Method(context, setString).Using("message", "serverError")).Do([](const std::string&, const std::string&) {
    return Status::OK;
  });

  When(Method(context, setEntity)).Do([=](const std::string& key, const Core::IEntity& entity) {
    REQUIRE(key == "innerStatus");
    REQUIRE(static_cast<const Status*>(&entity)->getStatusCode() == StatusCode::NotImplemented);
    return Status::OK;
  });

  ISerializer::Unique serializer = StatusSerializer::makeUnique();

  auto result = serializer->serialize(*status, context.get());
  REQUIRE(result.isOk() == true);

  Verify(Method(context, setString));
  Verify(Method(context, setEntity));
}

TEST_CASE("status serialization fails", "[StatusSerializer]") {
  Mock<ISerializationContext> context;

  SECTION("if setInt fails") {
    When(Method(context, setInt).Using("code", (int)StatusCode::OK)).Return(
      Status(StatusCode::NotImplemented, "error")
    );
  }

  SECTION("if setString fails") {
    When(Method(context, setInt).Using("code", (int)StatusCode::OK)).Return(
      Status::OK
    );
    When(Method(context, setString).Using("message", "serverError")).Return(
      Status(StatusCode::NotImplemented, "error")
    );
  }

  SECTION("if setEntity fails") {
    When(Method(context, setInt).Using("code", (int)StatusCode::OK)).Return(
      Status::OK
    );
    When(Method(context, setString).Using("message", "serverError")).Return(
      Status::OK
    );
    When(Method(context, setEntity)).Return(
      Status(StatusCode::NotImplemented, "error")
    );
  }

  auto innerStatus = Status::NotImplemented;
  auto status = Status::makeUnique(StatusCode::OK, "serverError", innerStatus);

  ISerializer::Unique serializer = StatusSerializer::makeUnique();
  auto result = serializer->serialize(*status, context.get());

  REQUIRE(result.isOk() == false);
}

TEST_CASE("status deserialization is not implemented", "[StatusSerializer]") {
  IEntity::Unique entity;
  Mock<IDeserializationContext> context;

  ISerializer::Unique serializer = StatusSerializer::makeUnique();

  auto result = serializer->deserialize(entity, context.get());
  REQUIRE(result.getStatusCode() == StatusCode::InternalServerError);
  REQUIRE(result.getInnerStatus()->getStatusCode() == StatusCode::NotImplemented);
}
