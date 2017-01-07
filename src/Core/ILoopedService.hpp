// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_I_LOOPED_SERVICE_HPP
#define CORE_I_LOOPED_SERVICE_HPP

#include "IEntity.hpp"

namespace Core {

class ILoopedService {
  TYPE_PTRS_ABSTRACT(ILoopedService)
  public:
      virtual ~ILoopedService();
      virtual void loop() = 0;
};

}

#endif /* end of include guard: CORE_I_LOOPED_SERVICE_HPP */
