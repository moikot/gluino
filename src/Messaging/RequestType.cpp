#include "RequestType.hpp"

using namespace Messaging;

RequestType RequestType::Create("create");
RequestType RequestType::Read("read");
RequestType RequestType::Update("update");
RequestType RequestType::Delete("delete");

RequestType::RequestType(std::string requestType) : requestType(requestType) {
}
