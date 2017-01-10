// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_MESSAGE_HPP
#define MESSAGING_MESSAGE_HPP

#include "ActionType.hpp"
#include "Core/IEntity.hpp"

#include <string>

namespace Messaging {

/**
  The base class for all the message (Request, Response and Notification).
*/
class Message : public Core::IEntity {
  TYPE_INFO(Message, IEntity, "message")
  public:
    /**
      Message priority.
    */
    enum class Priority {High, Mid, Low};

    /**
      The message sender.
    */
    std::string     getSender()     const { return sender; };

    /**
      The message receiver.
    */
    std::string     getReceiver()   const { return receiver; };

    /**
      The resource action type (Create, Get, Update, Delete).
    */
    ActionType      getActionType() const { return actionType; }

    /**
      The resource identifier.
    */
    std::string     getResource()   const { return resource; }

    /**
      The message priority.
    */
    Priority        getPriority()   const { return priority; }

  protected:
    Message(
      std::string   sender,
      std::string   receiver,
      ActionType    actionType,
      std::string   resource,
      Priority      priority
    );

  private:
    std::string   sender;
    std::string   receiver;
    ActionType    actionType;
    std::string   resource;
    Priority      priority;
};


}

#endif /* end of include guard: MESSAGING_MESSAGE_HPP */
