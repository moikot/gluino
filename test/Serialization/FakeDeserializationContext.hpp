// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef FAKE_DESERIALIZATION_CONTEXT
#define FAKE_DESERIALIZATION_CONTEXT

#include "Serialization/IDeserializationContext.hpp"

#include <string>

struct FakeDeserializationContext : public Serialization::IDeserializationContext {
  TYPE_PTRS(FakeDeserializationContext)

    virtual bool hasKey(const std::string&) override {
    throw std::runtime_error("hasKey call was not expected.");
  }

  virtual Core::Status getString(const std::string&, std::string&) override {
    throw std::runtime_error("getString call was not expected.");
  }

  virtual Core::Status getInt(const std::string&, int&) override {
    throw std::runtime_error("getInt call was not expected.");
  }

  virtual Core::Status getBool(const std::string&, bool&) override {
    throw std::runtime_error("getBool call was not expected.");
  }

  virtual Core::Status getEntity(const std::string&, Core::IEntity::Unique&) override {
    throw std::runtime_error("getEntity call was not expected.");
  }
};

#endif /* end of include guard: FAKE_DESERIALIZATION_CONTEXT */