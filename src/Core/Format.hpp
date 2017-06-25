// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_FORMAT_HPP
#define CORE_FORMAT_HPP

#include <string>
#include <memory>
#include <stdio.h>

namespace Core {

  template<typename ... Args>
  std::string stringFormat(const std::string& format, Args ... args) {
    char buffer [1];
    size_t size = snprintf(buffer, 1, format.c_str(), args ...) + sizeof('\0');
    std::unique_ptr<char[]> buf(new char[size]);
    snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), size - 1);
  }

  inline std::string toString(int val) {
    return stringFormat("%d", val);
  }

  inline std::string toString(unsigned val) {
    return stringFormat("%u", val);
  }

  inline std::string toString(long val) {
    return stringFormat("%ld", val);
  }

  inline std::string toString(unsigned long val) {
    return stringFormat("%lu", val);
  }

  inline std::string toString(long long val) {
    return stringFormat("%lld", val);
  }

  inline std::string toString(unsigned long long val) {
    return stringFormat("%llu", val);
  }

  inline std::string toString(float val) {
    return stringFormat("%f", val);
  }

  inline std::string toString(double val) {
    return stringFormat("%f", val);
  }

  inline std::string toString(long double val) {
    return stringFormat("%Lf", val);
  }

}

#endif /* end of include guard: CORE_FORMAT_HPP */
