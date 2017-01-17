// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_I_SERVICE_HPP
#define CORE_I_SERVICE_HPP

#include "Core/TypeInfo.hpp"

namespace Core {

/**
  The base class for all the services.
*/
class IService {
  TYPE_PTRS_ABSTRACT(IService)
  public:
      virtual ~IService() = default;

      /**
        This method should be invoked when the system is idle.
      */
      virtual void idle() = 0;
};

}

#endif /* end of include guard: CORE_I_SERVICE_HPP */
