// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_MESSAGE_HPP
#define CORE_MESSAGE_HPP

#include "IEntity.hpp"
#include "ActionType.hpp"

#include <string>

namespace Core {

class Message : public IEntity {
  TYPE_INFO(Message, IEntity, "message")
  
  public:
    enum class Priority {High, Mid, Low};

    std::string     getSender() const { return sender; };
    std::string     getReceiver() const { return receiver; };
    ActionType      getActionType() const { return actionType; }
    std::string     getResource() const { return resource; }
    Priority        getPriority() const { return priority; }

  protected:
    Message(
      std::string sender,
      std::string receiver,
      ActionType actionType,
      std::string resource,
      Priority priority
    );

  private:
    std::string sender;
    std::string receiver;
    ActionType actionType;
    std::string resource;
    Priority priority;
};


}

#endif /* end of include guard: CORE_MESSAGE_HPP */
