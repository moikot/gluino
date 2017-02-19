#include "Response.hpp"

using namespace Messaging;

Response::Response(std::string receiver, std::string requestType,
  std::string resource, std::unique_ptr<IEntity> content) :
  receiver(receiver), requestType(requestType),
  resource(resource), content(std::move(content)) {
}
