#include "ResponseSerializer.hpp"

using namespace Core;
using namespace Messaging;
using namespace Serialization;

#define FIELD_REQUEST_TYPE "requestType"
#define FIELD_RESOURCE "resource"
#define FIELD_CONTENT "content"

Status
ResponseSerializer::serializeImpl(ISerializationContext& context,
  const Response& response) const {

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

std::tuple<Core::Status, std::unique_ptr<Messaging::Response>>
ResponseSerializer::deserializeImpl(const IDeserializationContext&) const {
  return std::make_tuple(Status::NotImplemented, nullptr);
}
