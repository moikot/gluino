// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_LIST_SERIALIZER_HPP
#define SERIALIZATION_LIST_SERIALIZER_HPP

#include "Core/List.hpp"
#include "Serializer.hpp"

namespace Serialization {

template<typename T>
class ListSerializer : public Serializer<T> {
  TYPE_PTRS(ListSerializer<T>)
  typedef typename T::Unique TUnique;
  protected:
    // From Serializer
    virtual Core::Status serialize(
      const T& list,
      ISerializationContext& context) const override {

      auto result = context.setEntity("elements", list);
      if (!result.isOk())
        return result;

      return Core::Status::OK;
    }

    virtual Core::Status deserialize(
     TUnique& list,
     IDeserializationContext& context) const override {
       return Core::Status::NotImplemented;
    }
};

}

#endif /* end of include guard: SERIALIZATION_LIST_SERIALIZER_HPP */
