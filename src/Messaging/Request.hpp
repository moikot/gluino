// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_REQUEST_HPP
#define MESSAGING_REQUEST_HPP

#include "Core/IEntity.hpp"

namespace Messaging {

/**
  The request message.
*/
class Request : public Core::IEntity {
  TYPE_INFO(Request, IEntity, "request")
  public:
    /**
      Constructs a request.
    */
    Request(std::string sender, std::string requestType,
    std::string resource);

    /**
      Constructs a request.
    */
    Request(std::string sender, std::string requestType,
    std::string resource, std::unique_ptr<Core::IEntity> content);

    /**
      The request sender.
    */
    std::string getSender() const { return sender; };

    /**
      Set the request sender.
    */
    void setSender(std::string value) { sender = value; };

    /**
      The request type.
    */
    std::string getRequestType() const { return requestType; }

    /**
      The resource.
    */
    std::string getResource() const { return resource; }

    /**
      The request content.
    */
    const IEntity* getContent() const { return content.get(); };

  private:
    std::string     sender;
    std::string     requestType;
    std::string     resource;
    std::unique_ptr<IEntity> content;
};

}

#endif /* end of include guard: MESSAGING_MESSAGE_HPP */
