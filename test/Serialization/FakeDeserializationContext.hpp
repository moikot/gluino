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
  explicit FakeDeserializationContext(IDeserializationContext& context) : context(context) {
  }

  virtual bool hasKey(const std::string& key) override {
    return context.hasKey(key);
  }

  virtual Core::Status getString(const std::string& key, std::string& value) override {
    return context.getString(key, value);
  }

  virtual Core::Status getInt(const std::string& key, int& value) override {
    return context.getInt(key, value);
  }

  virtual Core::Status getBool(const std::string& key, bool& value) override {
    return context.getBool(key, value);
  }

  virtual Core::Status getEntity(const std::string& key, std::unique_ptr<Core::IEntity>& entity) override {
    return context.getEntity(key, entity);
  }

  private:
    IDeserializationContext& context;
};

#endif /* end of include guard: FAKE_DESERIALIZATION_CONTEXT */
