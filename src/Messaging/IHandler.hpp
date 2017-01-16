// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_I_HANDLER_HPP
#define MESSAGING_I_HANDLER_HPP

#include "Core/IEntity.hpp"

namespace Messaging {

/**
  The resource handler message.
*/
class IResourceHandler {
  TYPE_PTRS_ABSTRACT(IResourceHandler)

  virtual std::string getActionType() = 0;

  virtual std::string getContentType() = 0;

  virtual Core::IEntity::Unique makeRequest(const Core::IEntity* request) = 0;
};



}

#endif /* end of include guard: MESSAGING_I_HANDLER_HPP */
