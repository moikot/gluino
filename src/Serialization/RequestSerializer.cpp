#include "RequestSerializer.hpp"
#include "Core/Memory.hpp"

using namespace Core;
using namespace Messaging;
using namespace Serialization;

#define FIELD_REQUEST_TYPE "requestType"
#define FIELD_RESOURCE "resource"
#define FIELD_CONTENT "content"

Status
RequestSerializer::serializeImpl(ISerializationContext&, const Request&) const {
  return Status::NotImplemented;
}

std::tuple<Core::Status, std::unique_ptr<Messaging::Request>>
RequestSerializer::deserializeImpl(const IDeserializationContext& context) const {

  Status result;
  std::string requestType;
  std::tie(result, requestType) = context.getString(FIELD_REQUEST_TYPE);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  std::string resource;
  std::tie(result, resource) = context.getString(FIELD_RESOURCE);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  std::unique_ptr<IEntity> content;
  if (context.hasKey(FIELD_CONTENT)) {
    tie(result, content) = context.getEntity(FIELD_CONTENT);
    if (!result.isOk())
      return std::make_tuple(result, nullptr);
  }

  auto request = std::make_unique<Request>("", RequestType(requestType), resource, std::move(content));
  return std::make_tuple(Status::OK, std::move(request));
}
