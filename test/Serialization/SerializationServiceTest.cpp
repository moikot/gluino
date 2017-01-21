#include "Utils/Testing.hpp"

#include "Serialization/SerializationService.hpp"
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
  
  auto context = FakeSerializationContext::makeUnique();
  Mock<FakeSerializationContext> contextInstance(*context.get());

  When(Method(contextInstance, setString).Using("_type","content")).Do([](const std::string&, const std::string&) {
    return Status::OK;
  });

  When(Method(contextInstance, toString)).Return("serialized");

  Mock<IContextFactory> factoryInstance;
  When(Method(factoryInstance, createSerializationContext)).Do([&](
    const ISerializationService&,
    ISerializationContext::Unique& con) {
    con = std::move(context);
    return Status::OK;
  });

  Mock<ISerializer> serializerInstance;

  When(Method(serializerInstance, getTypeId)).Return(Content::TypeId());

  When(Method(serializerInstance, serialize)).Do([](
    const Core::IEntity&,
    ISerializationContext&) {
    return Status::OK;
  });

  auto serializer = ISerializer::Shared(&serializerInstance.get(), [](...) {});
  auto factory = IContextFactory::Shared(&factoryInstance.get(), [](...) {});

  auto service = SerializationService::makeUnique(factory);
  service->addSerializer(serializer);

  auto entity = Content::makeUnique();
  std::string json;
  auto result = service->serialize(*entity, json);
  REQUIRE(result.isOk() == true);
}

TEST_CASE("can deserialize an entity", "[SerializationService]") {
 
  auto context = FakeDeserializationContext::makeUnique();
  Mock<FakeDeserializationContext> contextInstance(*context.get());

  When(Method(contextInstance, getString)).Do([](const std::string&, std::string& value) {
    value = "content";
    return Status::OK;
  });

  Mock<IContextFactory> factoryInstance;

  When(Method(factoryInstance, createDeserializationContext)).Do([&](
    const ISerializationService&,
    const std::string&,
    IDeserializationContext::Unique& con) {
    con = std::move(context);
    return Status::OK;
  });

  Mock<ISerializer> serializerInstance;

  When(Method(serializerInstance, getTypeId)).Return(Content::TypeId());

  When(Method(serializerInstance, deserialize)).Do([](
    Core::IEntity::Unique& entity,
    IDeserializationContext&) {
    entity = Content::makeUnique();
    return Status::OK;
  });

  auto serializer = ISerializer::Shared(&serializerInstance.get(), [](...) {});
  auto factory = IContextFactory::Shared(&factoryInstance.get(), [](...) {});

  auto service = SerializationService::makeUnique(factory);
  service->addSerializer(serializer);

  Core::IEntity::Unique entity;
  auto result = service->deserialize("json", entity);
  REQUIRE(result.isOk() == true);
}
