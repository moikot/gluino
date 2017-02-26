#include "Utils/Testing.hpp"

#include "Core/Memory.hpp"
#include "Serialization/StatusSerializer.hpp"

using namespace Core;
using namespace Serialization;

using namespace fakeit;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

}

TEST_CASE("can serialize a status", "[StatusSerializer]") {
  auto innerStatus = Status::NotImplemented;
  auto status = std::make_unique<Status>(StatusCode::InternalServerError, "serverError", innerStatus);

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

  std::unique_ptr<ISerializer> serializer = std::make_unique<StatusSerializer>();

  auto result = serializer->serialize(context.get(), *status);
  REQUIRE(result.isOk() == true);

  Verify(Method(context, setString));
  Verify(Method(context, setEntity));
}

TEST_CASE("status serialization fails", "[StatusSerializer]") {
  Mock<ISerializationContext> context;

  SECTION("if setInt fails") {
    When(Method(context, setInt).Using("code", (int)StatusCode::OK)).Return(
      Status::NotImplemented
    );
  }

  SECTION("if setString fails") {
    When(Method(context, setInt).Using("code", (int)StatusCode::OK)).Return(
      Status::OK
    );
    When(Method(context, setString).Using("message", "serverError")).Return(
      Status::NotImplemented
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
      Status::NotImplemented
    );
  }

  auto innerStatus = Status::NotImplemented;
  auto status = std::make_unique<Status>(StatusCode::OK, "serverError", innerStatus);

  std::unique_ptr<ISerializer> serializer = std::make_unique<StatusSerializer>();
  auto result = serializer->serialize(context.get(), *status);

  REQUIRE(result.isOk() == false);
}

TEST_CASE("status deserialization is not implemented", "[StatusSerializer]") {
  Status result;
  std::unique_ptr<IEntity> entity;
  Mock<IDeserializationContext> context;

  std::unique_ptr<ISerializer> serializer = std::make_unique<StatusSerializer>();

  std::tie(result, entity) = serializer->deserialize(context.get());
  REQUIRE(result.getStatusCode() == StatusCode::InternalServerError);
  REQUIRE(result.getInnerStatus()->getStatusCode() == StatusCode::NotImplemented);
}
