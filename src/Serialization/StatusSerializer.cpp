#include "StatusSerializer.hpp"

using namespace Serialization;
using namespace Core;

#define FIELD_CODE "code"
#define FIELD_MESSAGE "message"
#define FIELD_INNER_STATUS "innerStatus"

Core::Status
StatusSerializer::serializeImpl(ISerializationContext& context, const Status& status) const {

  auto result = context.setInt(FIELD_CODE, (int)status.getStatusCode());
  if (!result.isOk())
    return result;

  result =context.setString(FIELD_MESSAGE, status.getMessage());
  if (!result.isOk())
    return result;

  auto innerStatus = status.getInnerStatus();
  if (innerStatus != nullptr) {
    result = context.setEntity(FIELD_INNER_STATUS, *innerStatus);
    if (!result.isOk())
      return result;
  }

  return Status::OK;
}

std::tuple<Core::Status, std::unique_ptr<Core::Status>>
StatusSerializer::deserializeImpl(const IDeserializationContext&) const {
  return std::make_tuple(Status::NotImplemented, nullptr);
}
