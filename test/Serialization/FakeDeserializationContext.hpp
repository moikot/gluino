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

  virtual bool hasKey(const std::string& key) const override {
    return context.hasKey(key);
  }

  virtual std::tuple<Core::Status, std::string> getString(const std::string& key) const override {
    return context.getString(key);
  }

  virtual std::tuple<Core::Status, int> getInt(const std::string& key) const override {
    return context.getInt(key);
  }

  virtual std::tuple<Core::Status, bool> getBool(const std::string& key) const override {
    return context.getBool(key);
  }

  virtual std::tuple<Core::Status, std::unique_ptr<Core::IEntity>> getEntity(const std::string& key) const override {
    return context.getEntity(key);
  }

  private:
    IDeserializationContext& context;
};

#endif /* end of include guard: FAKE_DESERIALIZATION_CONTEXT */
