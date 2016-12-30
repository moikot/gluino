// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_LIST_HPP
#define CORE_LIST_HPP

#include "IList.hpp"

#include <list>

namespace Core {

template <class T>
class List : public IList {
  public:
    // From IList
    virtual Core::StatusResult::Unique add(
      const IEntity& item) const override {
      return add((const T&)item);
    }

    virtual Core::StatusResult::Unique
      forEach(ForEachFunction func) const override {
      return forEach([&](const T& element) {
        return func(element);
      });
    };

    Core::StatusResult::Unique add(const T& value) {
      elements.push_back(value);
      return Core::StatusResult::OK();
    };

    typedef std::function<Core::StatusResult::Unique
      (const T& item)> ForEachFunctionTyped;

    Core::StatusResult::Unique forEach(ForEachFunctionTyped func) const {
      for(auto element: elements) {
        auto result = func(element);
        if (!result->isOk())
          return result;
      }
      return Core::StatusResult::OK();
    };

  private:
    std::list<T> elements;
 };

}

#endif /* end of include guard: CORE_LIST_HPP */
