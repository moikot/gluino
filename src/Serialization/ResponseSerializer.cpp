#include "ResponseSerializer.hpp"

using namespace Core;
using namespace Messaging;
using namespace Serialization;

#define FIELD_REQUEST_TYPE "requestType"
#define FIELD_RESOURCE "resource"
#define FIELD_CONTENT "content"

Status
ResponseSerializer::serialize(
  const Response& response,
  ISerializationContext& context) const {

  auto result = context.setString(FIELD_REQUEST_TYPE, response.getRequestType());
  if (!result.isOk())
    return result;

  result = context.setString(FIELD_RESOURCE, response.getResource());
  if (!result.isOk())
    return result;

  result = context.setEntity(FIELD_CONTENT, response.getContent());
  if (!result.isOk())
    return result;

  return Status::OK;
}

Status
ResponseSerializer::deserialize(Response::Unique&, IDeserializationContext&) const {
  return Status::NotImplemented;
}
