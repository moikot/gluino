#include "StatusSerializer.hpp"

using namespace Serialization;
using namespace Core;

#define FIELD_CODE "code"
#define FIELD_MESSAGE "message"
#define FIELD_INNER_STATUS "innerStatus"

Core::Status
StatusSerializer::serialize(const Status& status,
                            ISerializationContext& context) const {

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

Core::Status
StatusSerializer::deserialize(std::unique_ptr<Status>&, IDeserializationContext&) const {
  return Status::NotImplemented;
}
