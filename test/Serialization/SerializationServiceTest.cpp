#include "Utils/Testing.hpp"

#include "Serialization/SerializationService.hpp"
#include "Serialization/FakeSerializer.hpp"
#include "Serialization/FakeSerializationContext.hpp"
#include "Serialization/FakeDeserializationContext.hpp"

using namespace Core;
using namespace Serialization;

using namespace fakeit;
using namespace std::placeholders;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

}

TEST_CASE("can serialize an entity", "[SerializationService]") {
  Mock<ISerializationContext> context;
  Mock<IContextFactory> factoryInstance;
  Mock<ISerializer> serializerInstance;

  auto serializer = FakeSerializer::makeUnique(serializerInstance.get());
  auto service = SerializationService::makeUnique(factoryInstance.get());

  When(Method(context, setString).Using("_type","content")).Do([](const std::string&, const std::string&) {
    return Status::OK;
  });

  When(Method(context, toString)).Return("serialized");

  When(Method(factoryInstance, createSerializationContext)).Do([&](
    const ISerializationService&,
    ISerializationContext::Unique& con) {
    con = FakeSerializationContext::makeUnique(context.get());
    return Status::OK;
  });

  When(Method(serializerInstance, getTypeId)).Return(Content::TypeId());

  When(Method(serializerInstance, serialize)).Do([](
    const Core::IEntity&,
    ISerializationContext&) {
    return Status::OK;
  });

  service->addSerializer(std::move(serializer));

  auto entity = Content::makeUnique();
  std::string json;
  auto result = service->serialize(*entity, json);

  REQUIRE(result.isOk() == true);
}

TEST_CASE("entity serialization fails", "[SerializationService]") {
  Mock<ISerializationContext> context;
  Mock<IContextFactory> factoryInstance;
  Mock<ISerializer> serializerInstance;

  auto serializer = FakeSerializer::makeUnique(serializerInstance.get());
  auto service = SerializationService::makeUnique(factoryInstance.get());

  SECTION("if createSerializationContext fails") {
    When(Method(factoryInstance, createSerializationContext)).Do([&](
      const ISerializationService&,
      ISerializationContext::Unique&) {
      return Status::NotImplemented;
    });
    service->addSerializer(std::move(serializer));
  }

  SECTION("if setString for _type fails") {
    When(Method(factoryInstance, createSerializationContext)).Do([&](
      const ISerializationService&,
      ISerializationContext::Unique& con) {
      con = FakeSerializationContext::makeUnique(context.get());
      return Status::OK;
    });
    When(Method(context, setString).Using("_type","content")).Do([](const std::string&, const std::string&) {
      return Status::NotImplemented;
    });
    service->addSerializer(std::move(serializer));
  }

  SECTION("if the serializer is not found") {
    When(Method(factoryInstance, createSerializationContext)).Do([&](
      const ISerializationService&,
      ISerializationContext::Unique& con) {
      con = FakeSerializationContext::makeUnique(context.get());
      return Status::OK;
    });
    When(Method(context, setString).Using("_type","content")).Do([](const std::string&, const std::string&) {
      return Status::OK;
    });
  }

  auto entity = Content::makeUnique();
  std::string json;
  auto result = service->serialize(*entity, json);

  REQUIRE(result.isOk() == false);
}

TEST_CASE("can deserialize an entity", "[SerializationService]") {
  Mock<IDeserializationContext> context;
  Mock<IContextFactory> factoryInstance;
  Mock<ISerializer> serializerInstance;

  auto serializer = FakeSerializer::makeUnique(serializerInstance.get());
  auto service = SerializationService::makeUnique(factoryInstance.get());

  When(Method(context, getString)).Do([](const std::string&, std::string& value) {
    value = "content";
    return Status::OK;
  });

  When(Method(factoryInstance, createDeserializationContext)).Do([&](
    const ISerializationService&,
    const std::string&,
    IDeserializationContext::Unique& con) {
    con = FakeDeserializationContext::makeUnique(context.get());
    return Status::OK;
  });

  When(Method(serializerInstance, getTypeId)).Return(Content::TypeId());

  When(Method(serializerInstance, deserialize)).Do([](
    Core::IEntity::Unique& entity,
    IDeserializationContext&) {
    entity = Content::makeUnique();
    return Status::OK;
  });

  service->addSerializer(std::move(serializer));

  Core::IEntity::Unique entity;
  auto result = service->deserialize("json", entity);

  REQUIRE(result.isOk() == true);
}

TEST_CASE("entity deserialization fails", "[SerializationService]") {
  Mock<IDeserializationContext> context;
  Mock<IContextFactory> factoryInstance;
  Mock<ISerializer> serializerInstance;

  auto serializer = FakeSerializer::makeUnique(serializerInstance.get());
  auto service = SerializationService::makeUnique(factoryInstance.get());

  SECTION("if createDeserializationContext fails") {
    When(Method(factoryInstance, createDeserializationContext)).Do([&](
      const ISerializationService&,
      const std::string&,
      IDeserializationContext::Unique&) {
      return Status::NotImplemented;
    });
    service->addSerializer(std::move(serializer));
  }

  SECTION("if getString for _type fails") {
    When(Method(context, getString)).Do([](const std::string&, std::string&) {
      return Status::NotImplemented;
    });
    When(Method(factoryInstance, createDeserializationContext)).Do([&](
      const ISerializationService&,
      const std::string&,
      IDeserializationContext::Unique& con) {
      con = FakeDeserializationContext::makeUnique(context.get());
      return Status::OK;
    });
    service->addSerializer(std::move(serializer));
  }

  SECTION("if the serializer is not found") {
    When(Method(context, getString)).Do([](const std::string&, std::string& value) {
      value = "content";
      return Status::OK;
    });
    When(Method(factoryInstance, createDeserializationContext)).Do([&](
      const ISerializationService&,
      const std::string&,
      IDeserializationContext::Unique& con) {
      con = FakeDeserializationContext::makeUnique(context.get());
      return Status::OK;
    });
  }

  Core::IEntity::Unique entity;
  auto result = service->deserialize("json", entity);

  REQUIRE(result.isOk() == false);
}
