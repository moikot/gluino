// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef FAKE_SERIALIZATION_CONTEXT
#define FAKE_SERIALIZATION_CONTEXT

#include "Serialization/ISerializationContext.hpp"

#include <string>

struct FakeSerializationContext : public Serialization::ISerializationContext {
  TYPE_PTRS(FakeSerializationContext)

    virtual std::string toString() const override {
    throw std::runtime_error("toStirng call was not expected.");
  }

  virtual Core::Status setString(const std::string&, const std::string&) override {
    throw std::runtime_error("setStirng call was not expected.");
  }

  virtual Core::Status setInt(const std::string&, int) override {
    throw std::runtime_error("setInt call was not expected.");
  }

  virtual Core::Status setBool(const std::string&, bool) override {
    throw std::runtime_error("setBool call was not expected.");
  }

  virtual Core::Status setList(const std::string&, const Core::IList&) override {
    throw std::runtime_error("setList call was not expected.");
  }

  virtual Core::Status setEntity(const std::string&, const Core::IEntity&) override {
    throw std::runtime_error("setEntity call was not expected.");
  }
};

#endif /* end of include guard: FAKE_SERIALIZATION_CONTEXT */
