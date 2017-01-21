#include "StatusSerializer.hpp"

using namespace Serialization;
using namespace Core;

#define FIELD_CODE "code"
#define FIELD_MESSAGE "message"
#define FIELD_INNER_RESULT "innerResult"

Core::Status::Unique
StatusSerializer::serialize(const Status& status,
                            ISerializationContext& context) const {

  auto result = context.setInt(FIELD_CODE, (int)status.getStatusCode());
  if (!result->isOk())
    return result;

  result =context.setString(FIELD_MESSAGE, status.getMessage());
  if (!result->isOk())
    return result;

  auto innerResult = status.getInnerResult();
  if (innerResult != nullptr) {
    result = context.setEntity(FIELD_INNER_RESULT, *innerResult);
    if (!result->isOk())
      return result;
  }

  return Status::OK();
}

Core::Status::Unique
StatusSerializer::deserialize(Status::Unique&, IDeserializationContext&) const {
  return Status::NotImplemented();
}
