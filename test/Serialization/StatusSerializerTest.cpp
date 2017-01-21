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
  auto innerResult = Status::makeUnique(StatusCode::NotImplemented, "notImplemented");
  auto innerResultPtr = innerResult.get();
  auto status = Status::makeUnique(StatusCode::InternalServerError, "serverError", std::move(innerResult));

  Mock<ISerializationContext> context;

  When(Method(context, setInt).Using("code", (int)StatusCode::InternalServerError)).Do([](const std::string&, int) {
    return Status::OK();
  });

  When(Method(context, setString).Using("message", "serverError")).Do([](const std::string&, const std::string&) {
    return Status::OK();
  });

  When(Method(context, setEntity)).Do([=](const std::string& key, const Core::IEntity& entity) {
    REQUIRE(key == "innerResult");
    REQUIRE(&entity == innerResultPtr);
    return Status::OK();
  });

  ISerializer::Unique serializer = StatusSerializer::makeUnique();

  auto result = serializer->serialize(*status, context.get());
  REQUIRE(result->isOk() == true);

  Verify(Method(context, setString));
  Verify(Method(context, setEntity));
}

TEST_CASE("status deserialization is not implemented", "[StatusSerializer]") {
  IEntity::Unique entity;
  Mock<IDeserializationContext> context;

  ISerializer::Unique serializer = StatusSerializer::makeUnique();

  auto result = serializer->deserialize(entity, context.get());
  REQUIRE(result->getStatusCode() == StatusCode::InternalServerError);
  REQUIRE(result->getInnerResult()->getStatusCode() == StatusCode::NotImplemented);
}
