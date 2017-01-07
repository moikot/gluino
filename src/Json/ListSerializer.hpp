// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef JSON_LIST_SERIALIZER_HPP
#define JSON_LIST_SERIALIZER_HPP

#include "Core/List.hpp"
#include "Serializer.hpp"

namespace Json {

template<typename T>
class ListSerializer : public Serializer<T> {
  TYPE_PTRS(ListSerializer<T>)
  typedef typename T::Unique TUnique;
  protected:
    // From Serializer
    virtual Core::StatusResult::Unique serialize(
      const T& list,
      ISerializationContext& context) const override {

      auto result = context.setValue("elements", list);
      if (!result->isOk())
        return result;

      return Core::StatusResult::OK();
    }

    virtual Core::StatusResult::Unique deserialize(
     TUnique& list,
     ISerializationContext& context) const override {
       return Core::StatusResult::NotImplemented();
    }
};

}

#endif /* end of include guard: JSON_LIST_SERIALIZER_HPP */
