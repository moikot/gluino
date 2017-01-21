// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_I_LOGGER_HPP
#define CORE_I_LOGGER_HPP

#include "Core/TypeInfo.hpp"

namespace Core {

struct ILogger {
  TYPE_PTRS_ABSTRACT(ILogger)
  virtual ~ILogger() = default;

  virtual void message(const std::string& message) = 0;
  virtual void warning(const std::string& message) = 0;
  virtual void error(const std::string& message) = 0;
};

}

#endif /* end of include guard: CORE_LOGGER_HPP */
