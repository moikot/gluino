#include "ActionType.hpp"

using namespace Messaging;

const ActionType ActionType::Unknown  = ActionType("unknown");
const ActionType ActionType::Get      = ActionType("get");
const ActionType ActionType::Create   = ActionType("create");
const ActionType ActionType::Update   = ActionType("update");
const ActionType ActionType::Delete   = ActionType("delete");
