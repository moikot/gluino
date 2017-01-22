#include "SerializationService.hpp"

#include <algorithm>

using namespace Serialization;
using namespace Core;

#define TYPE_FIELD "_type"

SerializationService::SerializationService(
  std::shared_ptr<const IContextFactory> contextFactory) :
  contextFactory(contextFactory) {
}

Core::Status
SerializationService::serialize(
  const IEntity& entity,
  std::string& json) const {

  ISerializationContext::Unique context;
  auto result = contextFactory->createSerializationContext(*this, context);
  if (!result.isOk())
    return result;

  result = serialize(entity, *context);
  if (!result.isOk())
    return result;

  json = context->toString();
  return Status::OK;
}

Core::Status
SerializationService::serialize (
  const IEntity& entity,
  ISerializationContext& context) const {

  std::string typeId = entity.getTypeId();
  auto result = context.setString(TYPE_FIELD, typeId);
  if (!result.isOk())
    return result;

  auto serializer = getSerialzier(typeId);
  if (!serializer) {
    return Status(StatusCode::BadRequest,
      "Unable to find a serializer for type """ + typeId + """.");
  }
  return serializer->serialize(entity, context);
}

Core::Status
SerializationService::deserialize(
  const std::string& json,
  Core::IEntity::Unique& entity) const {

  IDeserializationContext::Unique context;
  auto result = contextFactory->createDeserializationContext(*this, json, context);
  if (!result.isOk())
    return result;

  return deserialize(*context, entity);
}

Core::Status
SerializationService::deserialize(
  IDeserializationContext& context,
  Core::IEntity::Unique& entity) const {

  std::string typeId;
  auto result = context.getString(TYPE_FIELD, typeId);
  if (!result.isOk())
    return result;

  auto serializer = getSerialzier(typeId);
  if (!serializer) {
    return Status(StatusCode::BadRequest,
      "Unable to find serializer for type """ + typeId + """.");
  }
  return serializer->deserialize(entity, context);
}

void
SerializationService::addSerializer(
  ISerializer::Shared serializer) {
  serializers.push_back(serializer);
}

std::shared_ptr<const ISerializer>
SerializationService::getSerialzier(std::string typeId) const {

  auto findIter = std::find_if(serializers.begin(), serializers.end(),
    [&](std::shared_ptr<const ISerializer> serializer){
      return serializer->getTypeId() == typeId;
    });

  if (findIter == serializers.end())
    return nullptr;

  return *findIter;
}
