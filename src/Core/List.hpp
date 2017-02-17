// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_LIST_HPP
#define CORE_LIST_HPP

#include "IList.hpp"

#include <list>

namespace Core {

template <class T>
class List : public IList {
  public:
    // From IList
    virtual Core::Status add(const IEntity& item) const override {
      return add((const T&)item);
    }

    virtual Core::Status forEach(ForEachFunction func) const override {
      return forEach([&](const T& element) {
        return func(element);
      });
    };

    // List
    Core::Status add(const T& value) {
      elements.push_back(value);
      return Core::Status::OK;
    };

    template<typename TFunc>
    Core::Status forEach(TFunc func) const {
      for(auto element: elements) {
        auto result = func(element);
        if (!result.isOk())
          return result;
      }
      return Core::Status::OK;
    };

  private:
    std::list<T> elements;
 };

}

#endif /* end of include guard: CORE_LIST_HPP */
