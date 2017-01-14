// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_RESPONSE_HPP
#define MESSAGING_RESPONSE_HPP

#include "Message.hpp"
#include "Core/IEntity.hpp"

namespace Messaging {

/**
  The response message.
*/
class Response : public Message {
  TYPE_INFO(Response, Message, "response")
  public:
    Response(
      std::string       sender,
      std::string       receiver,
      ActionType        actionType,
      std::string       resource,
      IEntity::Unique   content
    );

    /**
      The result of the action.
    */
    const IEntity& getResult() const { return *content; }

  private:
    IEntity::Unique content;
};

}

#endif /* end of include guard: MESSAGING_RESPONSE_HPP */
