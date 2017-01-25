// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_RESPONSE_HPP
#define MESSAGING_RESPONSE_HPP

#include "Core/IEntity.hpp"

namespace Messaging {

/**
  The response message.
*/
class Response : public Core::IEntity {
  TYPE_INFO(Response, IEntity, "response")
  public:
	/**
	Constructs a response.
	*/
    Response(std::string receiver, std::string requestType, 
		std::string resource, IEntity::Unique content);

	/**
	Constructs a response based on anther one and replaces the receiver.
	*/
	Response(std::string receiver, Response&& response);

	/**
	Move semantic.
	*/
	Response(Response && op) = default;
	Response& operator=(Response && op) = default;

	/**
	Copy semantic.
	*/
	Response(const Response& op) = delete;
	Response& operator=(const Response& op) = delete;

	/**
	The response receiver.
	*/
	std::string getReceiver() const { return receiver; };

    /**
      The request type (create, get, update, delete etc.).
    */
    std::string getRequestType() const { return requestType; }

    /**
      The resource identifier.
    */
    std::string getResource() const { return resource; }

    /**
      The response content.
    */
    const IEntity& getContent() const { return *content; }

  private:
	std::string     receiver;
    std::string     requestType;
    std::string     resource;
    IEntity::Unique content;
};

}

#endif /* end of include guard: MESSAGING_RESPONSE_HPP */
