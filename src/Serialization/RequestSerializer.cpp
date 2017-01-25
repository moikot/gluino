#include "RequestSerializer.hpp"

using namespace Core;
using namespace Messaging;
using namespace Serialization;

#define FIELD_REQUEST_TYPE "requestType"
#define FIELD_RESOURCE "resource"
#define FIELD_CONTENT "content"

Status
RequestSerializer::serialize(const Request&, ISerializationContext&) const {
  return Status::NotImplemented;
}

Status
RequestSerializer::deserialize(
  Request::Unique& request,
  IDeserializationContext& context) const {

  std::string requestType;
  auto result = context.getString(FIELD_REQUEST_TYPE, requestType);
  if (!result.isOk())
    return result;

  std::string resource;
  result = context.getString(FIELD_RESOURCE, resource);
  if (!result.isOk())
    return result;

  Core::IEntity::Unique content;
  if (context.hasKey(FIELD_CONTENT)) {
    result = context.getEntity(FIELD_CONTENT, content);
    if (!result.isOk())
      return result;
  }

  request = Request::makeUnique("", requestType, resource, std::move(content));
  return Status::OK;
}
