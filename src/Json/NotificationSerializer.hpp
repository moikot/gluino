// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef JSON_NOTIFICATION_SERIALIZER_HPP
#define JSON_NOTIFICATION_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Core/Notification.hpp"

namespace Json {

class NotificationSerializer : public Serializer<Core::Notification> {
  TYPE_PTRS(NotificationSerializer)
  protected:
    // From Serializer
    virtual Core::StatusResult::Unique serialize(
      const Core::Notification& notification,
      ISerializationContext& context) const override;

    virtual Core::StatusResult::Unique deserialize(
      Core::Notification::Unique& notification,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_NOTIFICATION_SERIALIZER_HPP */
