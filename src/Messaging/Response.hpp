// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_RESPONSE_HPP
#define CORE_RESPONSE_HPP

#include "Message.hpp"
#include "ActionResult.hpp"

namespace Core {

class Response : public Message {
  TYPE_INFO(Response, Message, "response")
  public:
    Response(
      std::string sender,
      std::string receiver,
      ActionType actionType,
      std::string resource,
      ActionResult::Unique result
    );

    const ActionResult& getResult() const { return *result; }

  private:
    ActionResult::Unique result;
};

}

#endif /* end of include guard: CORE_RESPONSE_HPP */
