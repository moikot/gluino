// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_NOTIFICATION_SERIALIZER_HPP
#define SERIALIZATION_NOTIFICATION_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Messaging/Notification.hpp"

namespace Serialization {

class NotificationSerializer : public Serializer<Messaging::Notification> {
  TYPE_PTRS(NotificationSerializer)
  protected:
    // From Serializer
    virtual Core::StatusResult::Unique serialize(
      const Messaging::Notification& notification,
      ISerializationContext& context) const override;

    virtual Core::StatusResult::Unique deserialize(
      Messaging::Notification::Unique& notification,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_NOTIFICATION_SERIALIZER_HPP */
