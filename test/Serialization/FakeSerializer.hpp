// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef FAKE_SERIALIZER
#define FAKE_SERIALIZER

#include "Serialization/ISerializer.hpp"

struct FakeSerializer : public Serialization::ISerializer {
  explicit FakeSerializer(ISerializer& serializer) : serializer(serializer) {
  }

  virtual const std::string& getTypeId() const {
    return serializer.getTypeId();
  }

  virtual Core::Status
    serialize(Serialization::ISerializationContext& context, const Core::IEntity& entity) const {
      return serializer.serialize(context, entity);
    }

  virtual std::tuple<Core::Status, std::unique_ptr<Core::IEntity>>
    deserialize(const Serialization::IDeserializationContext& context) const {
        return serializer.deserialize(context);
    }

  private:
    ISerializer& serializer;
};

#endif /* end of include guard: FAKE_SERIALIZER */
