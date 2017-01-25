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
      std::string resource, IEntity::Shared content);

  	/**
  	Constructs a request based on anther one and replaces the receiver.
  	*/
  	Request(std::string sender, Request&& request);

  	/**
  	The request sender.
  	*/
  	std::string getSender() const { return sender; };

    /**
      The request type (create, get, update, delete etc.).
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
    IEntity::Shared content;
};

}

#endif /* end of include guard: MESSAGING_MESSAGE_HPP */
