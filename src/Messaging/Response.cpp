#include "Response.hpp"

using namespace Messaging;

Response::Response(
  std::string requestType,
  std::string receiver,
  std::string resource,
  IEntity::Shared content
) :
  requestType(requestType),
  receiver(receiver),
  resource(resource),
  content(content) {
}
