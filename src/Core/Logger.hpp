// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_LOGGER_HPP
#define CORE_LOGGER_HPP

#include <string>

namespace Core {

class Logger {
  public:
    static void initialize();

    static void message(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);
};

}

#endif /* end of include guard: CORE_LOGGER_HPP */
