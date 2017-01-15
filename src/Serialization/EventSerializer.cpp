#include "EventSerializer.hpp"

using namespace Core;
using namespace Messaging;
using namespace Serialization;

#define FIELD_ACTION "action"
#define FIELD_RESOURCE "resource"
#define FIELD_CONTENT "content"

StatusResult::Unique
EventSerializer::serialize(
  const Messaging::Event& event,
  ISerializationContext& context) const {

  auto result = context.setValue(FIELD_ACTION, event.getActionType().getId());
  if (!result->isOk())
    return result;

  result = context.setValue(FIELD_RESOURCE, event.getResource());
  if (!result->isOk())
    return result;

  auto content = event.getContent();
  if (content) {
    result = context.setValue(FIELD_CONTENT, *content);
    if (!result->isOk())
      return result;
  }

  return StatusResult::OK();
}

StatusResult::Unique
EventSerializer::deserialize(Event::Unique&, ISerializationContext&) const {
  return StatusResult::NotImplemented();
}
