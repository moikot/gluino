#include "ObjectResult.hpp"

using namespace Core;

ObjectResult::ObjectResult(StatusCode statusCode, IEntity::Unique entity) :
  statusCode(statusCode), entity(std::move(entity)) {

}
