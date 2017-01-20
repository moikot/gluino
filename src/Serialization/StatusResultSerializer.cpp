#include "StatusResultSerializer.hpp"

using namespace Serialization;
using namespace Core;

#define FIELD_CODE "code"
#define FIELD_MESSAGE "message"
#define FIELD_INNER_RESULT "innerResult"

Core::StatusResult::Unique
StatusResultSerializer::serialize(const StatusResult& statusResult,
                            ISerializationContext& context) const {

  auto result = context.setInt(FIELD_CODE, (int)statusResult.getStatusCode());
  if (!result->isOk())
    return result;

  result =context.setString(FIELD_MESSAGE, statusResult.getMessage());
  if (!result->isOk())
    return result;

  auto innerResult = statusResult.getInnerReuslt();
  if (innerResult != nullptr) {
    result = context.setEntity(FIELD_INNER_RESULT, *innerResult);
    if (!result->isOk())
      return result;
  }

  return StatusResult::OK();
}

Core::StatusResult::Unique
StatusResultSerializer::deserialize(StatusResult::Unique&, IDeserializationContext&) const {
  return StatusResult::NotImplemented();
}
