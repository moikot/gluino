// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_IDENTITY_HPP
#define CORE_IDENTITY_HPP

#include <string>
#include <random>
#include <algorithm>

namespace Core {

/**
  The base class for all the collections of domain objects.
*/
struct Identity  {

    /**
      Creates a new unique identity 8 characters long.

      @return The created identity.
    */
    static std::string create() {
      static auto randomChar = []() -> char
      {
          const char charset[] = "0123456789ABCDEF";
          return charset[rand() % 15];
      };
      std::string str(8,0);
      std::generate_n(str.begin(), 8, randomChar);
      return str;
    }
};

}

#endif /* end of include guard: CORE_IDENTITY_HPP */
