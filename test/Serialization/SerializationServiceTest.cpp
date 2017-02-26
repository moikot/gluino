#include "Utils/Testing.hpp"

#include "Core/Memory.hpp"
#include "Serialization/SerializationService.hpp"
#include "Serialization/FakeSerializer.hpp"
#include "Serialization/FakeSerializationContext.hpp"
#include "Serialization/FakeDeserializationContext.hpp"

using namespace Core;
using namespace Serialization;

using namespace fakeit;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

}

TEST_CASE("can serialize an entity", "[SerializationService]") {
  Mock<ISerializationContext> context;
  Mock<IContextFactory> factoryInstance;
  Mock<ISerializer> serializerInstance;

  auto serializer = std::make_unique<FakeSerializer>(serializerInstance.get());
  auto service = std::make_unique<SerializationService>(factoryInstance.get());

  When(Method(context, setString).Using("_type","content")).Do([](const std::string&, const std::string&) {
    return Status::OK;
  });

  When(Method(context, toString)).Return("serialized");

  When(Method(factoryInstance, createSerializationContext)).Do([&](
    const ISerializationService&) {
    auto con = std::make_unique<FakeSerializationContext>(context.get());
    return std::make_tuple(Status::OK, std::move(con));
  });

  When(Method(serializerInstance, getTypeId)).Return(Content::TypeId());

  When(Method(serializerInstance, serialize)).Do([](
        ISerializationContext&, const Core::IEntity&) {
    return Status::OK;
  });

  service->addSerializer(std::move(serializer));

  auto entity = std::make_unique<Content>();
  Status result;
  std::string json;
  std::tie(result, json) = service->serialize(*entity);

  REQUIRE(result.isOk() == true);
}

TEST_CASE("entity serialization fails", "[SerializationService]") {
  Mock<ISerializationContext> context;
  Mock<IContextFactory> factoryInstance;
  Mock<ISerializer> serializerInstance;

  auto serializer = std::make_unique<FakeSerializer>(serializerInstance.get());
  auto service = std::make_unique<SerializationService>(factoryInstance.get());

  SECTION("if createSerializationContext fails") {
    When(Method(factoryInstance, createSerializationContext)).Do([&](
      const ISerializationService&) {
      return std::make_tuple(Status::NotImplemented, std::unique_ptr<ISerializationContext>());
    });
  }

  SECTION("if setString for _type fails") {
    When(Method(factoryInstance, createSerializationContext)).Do([&](
      const ISerializationService&) {
      auto con = std::make_unique<FakeSerializationContext>(context.get());
      return std::make_tuple(Status::OK, std::move(con));
    });
    When(Method(context, setString).Using("_type","content")).Do([](const std::string&, const std::string&) {
      return Status::NotImplemented;
    });
  }

  SECTION("if the serializer is not found") {
    When(Method(factoryInstance, createSerializationContext)).Do([&](
      const ISerializationService&) {
      auto con = std::make_unique<FakeSerializationContext>(context.get());
      return std::make_tuple(Status::OK, std::move(con));
    });
    When(Method(context, setString).Using("_type","content")).Do([](const std::string&, const std::string&) {
      return Status::OK;
    });
  }

  auto entity = std::make_unique<Content>();
  Status result;
  std::string json;
  std::tie(result, json) = service->serialize(*entity);

  REQUIRE(result.isOk() == false);
}

TEST_CASE("can deserialize an entity", "[SerializationService]") {
  Mock<IDeserializationContext> context;
  Mock<IContextFactory> factoryInstance;
  Mock<ISerializer> serializerInstance;

  auto serializer = std::make_unique<FakeSerializer>(serializerInstance.get());
  auto service = std::make_unique<SerializationService>(factoryInstance.get());

  When(Method(context, getString)).Do([](const std::string&) {
    return std::make_tuple(Status::OK, "content");
  });

  When(Method(factoryInstance, createDeserializationContext)).Do([&](
    const ISerializationService&, const std::string&) {
    auto con = std::make_unique<FakeDeserializationContext>(context.get());
    return std::make_tuple(Status::OK, std::move(con));
  });

  When(Method(serializerInstance, getTypeId)).Return(Content::TypeId());

  When(Method(serializerInstance, deserialize)).Do([](
    const IDeserializationContext&) {
    auto entity = std::make_unique<Content>();
    return std::make_tuple(Status::OK, std::move(entity));
  });

  service->addSerializer(std::move(serializer));

  Status result;
  std::unique_ptr<IEntity> entity;
  std::tie(result, entity) = service->deserialize("json");

  REQUIRE(result.isOk() == true);
}

TEST_CASE("entity deserialization fails", "[SerializationService]") {
  Mock<IDeserializationContext> context;
  Mock<IContextFactory> factoryInstance;
  Mock<ISerializer> serializerInstance;

  auto serializer = std::make_unique<FakeSerializer>(serializerInstance.get());
  auto service = std::make_unique<SerializationService>(factoryInstance.get());

  SECTION("if createDeserializationContext fails") {
    When(Method(factoryInstance, createDeserializationContext)).Do([&](
      const ISerializationService&, const std::string&) {
      return Status::NotImplemented;
    });
    service->addSerializer(std::move(serializer));
  }

  SECTION("if getString for _type fails") {
    When(Method(context, getString)).Do([](const std::string&) {
      return std::make_tuple(Status::NotImplemented, "");
    });
    When(Method(factoryInstance, createDeserializationContext)).Do([&](
      const ISerializationService&, const std::string&) {
      auto con = std::make_unique<FakeDeserializationContext>(context.get());
      return std::make_tuple(Status::OK, std::move(con));
    });
    service->addSerializer(std::move(serializer));
  }

  SECTION("if the serializer is not found") {
    When(Method(context, getString)).Do([](const std::string&) {
      return std::make_tuple(Status::OK, "content");
    });
    When(Method(factoryInstance, createDeserializationContext)).Do([&](
      const ISerializationService&, const std::string&) {
      auto con = std::make_unique<FakeDeserializationContext>(context.get());
      return std::make_tuple(Status::OK, std::move(con));
    });
  }

  Status result;
  std::unique_ptr<IEntity> entity;
  std::tie(result, entity) = service->deserialize("json");

  REQUIRE(result.isOk() == false);
}
