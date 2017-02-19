#include "Utils/Testing.hpp"

#include "Core/Casting.hpp"
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

  auto serializer = makeUnique<FakeSerializer>(serializerInstance.get());
  auto service = makeUnique<SerializationService>(factoryInstance.get());

  When(Method(context, setString).Using("_type","content")).Do([](const std::string&, const std::string&) {
    return Status::OK;
  });

  When(Method(context, toString)).Return("serialized");

  When(Method(factoryInstance, createSerializationContext)).Do([&](
    const ISerializationService&,
    std::unique_ptr<ISerializationContext>& con) {
    con = makeUnique<FakeSerializationContext>(context.get());
    return Status::OK;
  });

  When(Method(serializerInstance, getTypeId)).Return(Content::TypeId());

  When(Method(serializerInstance, serialize)).Do([](
    const Core::IEntity&,
    ISerializationContext&) {
    return Status::OK;
  });

  service->addSerializer(std::move(serializer));

  auto entity = makeUnique<Content>();
  std::string json;
  auto result = service->serialize(*entity, json);

  REQUIRE(result.isOk() == true);
}

TEST_CASE("entity serialization fails", "[SerializationService]") {
  Mock<ISerializationContext> context;
  Mock<IContextFactory> factoryInstance;
  Mock<ISerializer> serializerInstance;

  auto serializer = makeUnique<FakeSerializer>(serializerInstance.get());
  auto service = makeUnique<SerializationService>(factoryInstance.get());

  SECTION("if createSerializationContext fails") {
    When(Method(factoryInstance, createSerializationContext)).Do([&](
      const ISerializationService&,
      std::unique_ptr<ISerializationContext>&) {
      return Status::NotImplemented;
    });
    service->addSerializer(std::move(serializer));
  }

  SECTION("if setString for _type fails") {
    When(Method(factoryInstance, createSerializationContext)).Do([&](
      const ISerializationService&,
      std::unique_ptr<ISerializationContext>& con) {
      con = makeUnique<FakeSerializationContext>(context.get());
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
      std::unique_ptr<ISerializationContext>& con) {
      con = makeUnique<FakeSerializationContext>(context.get());
      return Status::OK;
    });
    When(Method(context, setString).Using("_type","content")).Do([](const std::string&, const std::string&) {
      return Status::OK;
    });
  }

  auto entity = makeUnique<Content>();
  std::string json;
  auto result = service->serialize(*entity, json);

  REQUIRE(result.isOk() == false);
}

TEST_CASE("can deserialize an entity", "[SerializationService]") {
  Mock<IDeserializationContext> context;
  Mock<IContextFactory> factoryInstance;
  Mock<ISerializer> serializerInstance;

  auto serializer = makeUnique<FakeSerializer>(serializerInstance.get());
  auto service = makeUnique<SerializationService>(factoryInstance.get());

  When(Method(context, getString)).Do([](const std::string&, std::string& value) {
    value = "content";
    return Status::OK;
  });

  When(Method(factoryInstance, createDeserializationContext)).Do([&](
    const ISerializationService&,
    const std::string&,
    std::unique_ptr<IDeserializationContext>& con) {
    con = makeUnique<FakeDeserializationContext>(context.get());
    return Status::OK;
  });

  When(Method(serializerInstance, getTypeId)).Return(Content::TypeId());

  When(Method(serializerInstance, deserialize)).Do([](
    std::unique_ptr<IEntity>& entity,
    IDeserializationContext&) {
    entity = makeUnique<Content>();
    return Status::OK;
  });

  service->addSerializer(std::move(serializer));

  std::unique_ptr<IEntity> entity;
  auto result = service->deserialize("json", entity);

  REQUIRE(result.isOk() == true);
}

TEST_CASE("entity deserialization fails", "[SerializationService]") {
  Mock<IDeserializationContext> context;
  Mock<IContextFactory> factoryInstance;
  Mock<ISerializer> serializerInstance;

  auto serializer = makeUnique<FakeSerializer>(serializerInstance.get());
  auto service = makeUnique<SerializationService>(factoryInstance.get());

  SECTION("if createDeserializationContext fails") {
    When(Method(factoryInstance, createDeserializationContext)).Do([&](
      const ISerializationService&,
      const std::string&,
      std::unique_ptr<IDeserializationContext>&) {
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
      std::unique_ptr<IDeserializationContext>& con) {
      con = makeUnique<FakeDeserializationContext>(context.get());
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
      std::unique_ptr<IDeserializationContext>& con) {
      con = makeUnique<FakeDeserializationContext>(context.get());
      return Status::OK;
    });
  }

  std::unique_ptr<IEntity> entity;
  auto result = service->deserialize("json", entity);

  REQUIRE(result.isOk() == false);
}
