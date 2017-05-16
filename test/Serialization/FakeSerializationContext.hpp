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
  explicit FakeSerializationContext(ISerializationContext& context) : context(context) {
  }

  virtual std::string toString() const override {
    return context.toString();
  }

  virtual Core::Status setString(const std::string& key, const std::string& value) override {
    return context.setString(key, value);
  }

  virtual Core::Status setInt(const std::string& key, int value) override {
    return context.setInt(key, value);
  }

  virtual Core::Status setFloat(const std::string& key, float value) override {
    return context.setFloat(key, value);
  }

  virtual Core::Status setBool(const std::string& key, bool value) override {
    return context.setBool(key, value);
  }

  virtual Core::Status setList(const std::string& key, const Core::IList& list) override {
    return context.setList(key, list);
  }

  virtual Core::Status setEntity(const std::string& key, const Core::IEntity& entity) override {
    return context.setEntity(key, entity);
  }

  private:
    ISerializationContext& context;
};

#endif /* end of include guard: FAKE_SERIALIZATION_CONTEXT */
