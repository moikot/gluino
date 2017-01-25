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
	The response receiver.
	*/
	std::string getReceiver() const { return receiver; };

	/**
	Set the response receiver.
	*/
	void setReceiver(std::string value) { receiver = value; };

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
