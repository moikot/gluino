// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_REQUEST_HPP
#define MESSAGING_REQUEST_HPP

#include "Message.hpp"

namespace Messaging {

class Request : public Message {
  TYPE_INFO(Request, Message, "request")
  public:
    // Incomming requests
    Request(std::string sender, Request::Unique request);
    Request(ActionType actionType, std::string resource, IEntity::Unique content);

    // Internal requests
    Request(std::string sender, ActionType actionType, std::string resource);
    Request(std::string sender, ActionType actionType, std::string resource, IEntity::Unique content);

    const IEntity* getContent() const { return content.get(); };

  private:
    IEntity::Unique content;
};

}

#endif /* end of include guard: MESSAGING_MESSAGE_HPP */
