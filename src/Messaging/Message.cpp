#include "Message.hpp"

using namespace Messaging;

Message::Message(std::string sender, std::string receiver,
  ActionType actionType, std::string resource, Priority priority) :
  sender(sender), receiver(receiver),
  actionType(actionType), resource(resource), priority(priority) {
}
