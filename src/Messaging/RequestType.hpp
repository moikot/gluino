// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_REQUEST_TYPE_HPP
#define MESSAGING_REQUEST_TYPE_HPP

#include <string>

namespace Messaging {

/**
  The notification message.
*/
class RequestType {
  public:

    /**
  	  Create a resource.
  	*/
    static RequestType Create;

    /**
  	  Reade a resource.
  	*/
    static RequestType Read;

    /**
  	  Udate a resource.
  	*/
    static RequestType Update;

    /**
      Delete a resource.
    */
    static RequestType Delete;

  	/**
  	  Constructs an event type.
  	*/
    explicit RequestType(const std::string& requestType);

    /**
  	  Equality operators.
  	*/
    bool operator==(const RequestType& other) {
      return requestType == other.requestType;
    }

    bool operator!=(const RequestType& other) {
      return !(*this == other);
    }

    /**
  	  Convert to string.
  	*/
    operator const std::string() const { return requestType; }

  private:
    std::string     requestType;
};

}

#endif /* end of include guard: MESSAGING_REQUEST_TYPE_HPP */
