#include "Response.hpp"

using namespace Messaging;

Response::Response(std::string receiver, std::string requestType,
  std::string resource, IEntity::Unique content) :
  receiver(receiver), requestType(requestType),
  resource(resource), content(std::move(content)) {
}
