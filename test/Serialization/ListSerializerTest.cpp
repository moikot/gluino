#include "Utils/Testing.hpp"

#include "Core/Memory.hpp"
#include "Serialization/ListSerializer.hpp"

using namespace Core;
using namespace Serialization;

using namespace fakeit;

namespace {

  class Content : public IEntity {
    TYPE_INFO(Content, IEntity, "content")
  };

  class ContentCol : public Core::List<Content> {
    TYPE_INFO(Networks, List<Content>, "contentCol")
  };

}

TEST_CASE("can serialize a list", "[ListSerializer]") {
  auto content = std::make_unique<ContentCol>();
  auto contentPtr = content.get();

  Mock<ISerializationContext> context;

  When(Method(context, setList)).Do([=](const std::string& key, const Core::IEntity& entity) {
    REQUIRE(key == "elements");
    REQUIRE(&entity == contentPtr);
    return Status::OK;
  });

  std::unique_ptr<ISerializer> serializer = std::make_unique<ListSerializer<ContentCol>>();
  auto result = serializer->serialize(context.get(), *content);

  REQUIRE(result.isOk() == true);
  Verify(Method(context, setList));
}

TEST_CASE("list serialization fails", "[ListSerializer]") {
  Mock<ISerializationContext> context;

  SECTION("if setList fails") {
    When(Method(context, setList)).Return(
      Status::NotImplemented
    );
  }

  auto content = std::make_unique<ContentCol>();

  std::unique_ptr<ISerializer> serializer = std::make_unique<ListSerializer<ContentCol>>();
  auto result = serializer->serialize(context.get(), *content);

  REQUIRE(result.isOk() == false);
}

TEST_CASE("list deserialization is not implemented", "[ListSerializer]") {
  Status result;
  std::unique_ptr<IEntity> entity;
  Mock<IDeserializationContext> context;

  std::unique_ptr<ISerializer> serializer = std::make_unique<ListSerializer<ContentCol>>();
  std::tie(result, entity) = serializer->deserialize(context.get());

  REQUIRE(result.getStatusCode() == StatusCode::InternalServerError);
  REQUIRE(result.getInnerStatus()->getStatusCode() == StatusCode::NotImplemented);
}
