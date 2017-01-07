// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_MEMORY_HPP
#define CORE_MEMORY_HPP

#include <memory>

namespace Core {

// A simple implementation of make_unique
template <typename T, typename... Args>
std::unique_ptr<T> makeUnique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}

#endif /* end of include guard: CORE_MEMORY_HPP */
