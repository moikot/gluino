// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_REQUEST_HPP
#define MESSAGING_REQUEST_HPP

#include "Message.hpp"

namespace Messaging {

/**
  The request message.
*/
class Request : public Message {
  TYPE_INFO(Request, Message, "request")
  public:
    Request(
      std::string sender,
      ActionType actionType,
      std::string resource,
      IEntity::Unique content
    );

    /**
      The request payload.
    */
    const IEntity* getContent() const { return content.get(); };

  private:
    IEntity::Unique content;
};

}

#endif /* end of include guard: MESSAGING_MESSAGE_HPP */
