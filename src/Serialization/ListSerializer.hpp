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
  protected:
    // From Serializer
    virtual Core::Status
      serializeImpl(ISerializationContext& context, const T& list) const override {

      auto result = context.setEntity("elements", list);
      if (!result.isOk())
        return result;

      return Core::Status::OK;
    }

    virtual std::tuple<Core::Status, std::unique_ptr<T>>
    deserializeImpl(const IDeserializationContext&) const override {
       return std::make_tuple(Core::Status::NotImplemented, nullptr);
    }
};

}

#endif /* end of include guard: SERIALIZATION_LIST_SERIALIZER_HPP */
