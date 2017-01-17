// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_QUEUE_CLIENT_HPP
#define MESSAGING_QUEUE_CLIENT_HPP

#include "Response.hpp"
#include "Event.hpp"

namespace Messaging {

class QueueClient {
  TYPE_PTRS_ABSTRACT(QueueClient)
  public:
    virtual ~QueueClient() = default;

    virtual std::string getClientId() const = 0;
    virtual void onResponse(const Response& response) const = 0;
    virtual void onEvent(const Event& event) const = 0;
};

}

#endif /* end of include guard: MESSAGING_QUEUE_CLIENT_HPP */
