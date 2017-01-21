// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_I_SERIALIZATION_CONTEXT_HPP
#define SERIALIZATION_I_SERIALIZATION_CONTEXT_HPP

#include "Core/Status.hpp"
#include "Core/IList.hpp"

namespace Serialization {

class ISerializationContext {
  TYPE_PTRS_ABSTRACT(ISerializationContext)
  public:
    virtual ~ISerializationContext() = default;

    virtual std::string toString() const = 0;

    virtual Core::Status
      setString(const std::string& key, const std::string& value) = 0;
    virtual Core::Status
      setInt(const std::string& key, int value) = 0;
    virtual Core::Status
      setBool(const std::string& key, bool value) = 0;
    virtual Core::Status
      setList(const std::string& key, const Core::IList& list) = 0;
    virtual Core::Status
      setEntity(const std::string& key, const Core::IEntity& entity) = 0;
};

}

#endif /* end of include guard: SERVICES_I_SERIALIZATION_CONTEXT_HPP */
