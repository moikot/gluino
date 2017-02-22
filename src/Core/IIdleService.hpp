// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_I_IDLE_SERVICE_HPP
#define CORE_I_IDLE_SERVICE_HPP

#include "Core/IEntity.hpp"

namespace Core {

/**
  The base class for idle services.
*/
struct IIdleService : public IEntity  {
  TYPE_INFO(IIdleService, IEntity, "idleService")
  virtual ~IIdleService() = default;
  virtual void idle() = 0;
};

}

#endif /* end of include guard: CORE_I_IDLE_SERVICE_HPP */
