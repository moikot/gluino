# Gluino
[![Build Status](https://api.travis-ci.org/anisimovsergey/gluino.svg?branch=master)](https://travis-ci.org/anisimovsergey/gluino?branch=master)
[![Build status](https://ci.appveyor.com/api/projects/status/oiyjkkvbiyfy2u0h?svg=true)](https://ci.appveyor.com/project/anisimovsergey/gluino)
[![Coverage Status](https://coveralls.io/repos/github/anisimovsergey/gluino/badge.svg?branch=master)](https://coveralls.io/github/anisimovsergey/gluino?branch=master)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/74ecfbf675f34a3192ee0894ba75043e)](https://www.codacy.com/app/anisimovsergey/gluino?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=anisimovsergey/gluino&amp;utm_campaign=Badge_Grade)

## The message queue

All the messages in the system are divided into three types: requests, responses and events. Request are added to the message queue and processed in FIFO order.

### Request
The request message (Request class) is send by resource clients (QueueResourceClient class) and handled by resource controllers (QueueResourceController class).

```cpp
  auto connection = std::make_unique<ConnectionParams>("WIFI_NAME", "PASSWORD");
  auto request = std::make_unique<Request>("clientId", RequestType::Create, "connection", std::move(connection));
```

### Response
The response message (Response class) is sent by queue resource controllers (QueueResourceController class) in the result of handling a request sent by a resource client (QueueResourceClient class).

```cpp
  auto status = std::make_unique<Status>(StatusCode::Created, "The connection was created.");
  auto response = std::make_unique<Response>("clientId", RequestType::Create, "connection", std::move(status));
```

### Events
The event message (Event class) is sent by queue resource controllers (QueueResourceController class) in order to notify all the queue resource clients abut some changes in the resource state.

```cpp
  auto connection = std::make_unique<Connection>("WIFI_NAME", isConnected);
  auto event = std::make_unique<Event>(EventType::Created, "connection", std::move(connection));
```

### Queue resource client
The queue resource client can be used to get access to a resource and perform  operations with it. A resource client is created using IMessageQueue.createClient during its creation the client gets added to the resource clients list of the queue and automatically removed when it goes out of scope.

```cpp
  colorClient = messageQueue.createClient("SenderId", Color::TypeId());
  colorClient->addOnResponse(RequestType::Read, [=](const Color& color) {
    onColorReadResponse(color);
  });
  colorClient->addOnEvent(EventType::Updated, [=](const Color& color) {
    onColorUpdatedEvent(color);
  });
```

The queue resource client simplifies the request sending by automatically including the client id and the resource type to the requests.

```cpp
  auto newColor = std::make_unique<Color>(r, g, b);
  colorClient->sendRequest(RequestType::Update, std::move(newColor));
```

### Queue resource controllers
The queue resource controller is handling requests to a particular resource. The requests can involve a modification of the resource or can be just simple read. In the former case the response should contain only the operation status and the new (modified) resource representation can be sent in the correspondent notification ore explicitly retrieved by an idempotent read request.

```cpp
  colorController = messageQueue.createController(Models::Color::TypeId());
  colorController->addOnRequest(RequestType::Update, [=](const Color& model){
    setColor(model);
    colorController->sendEvent(EventType::Updated, std::make_unique<Color>(model));
    return std::make_unique<Status>(Status::OK);
  });
```

In case of a read request the response should contain the resource representation if the request was successful or status otherwise.

```cpp
  connectionController = messageQueue.createController(Connection::TypeId());
  connectionController->addOnRequest(RequestType::Read, [=](){
    if (hasConnection()) {
      return createConnectionObject();
    } else {
      return std::make_unique<Status>(StatusCode::NotFound, "The connection doesn't exist.");
    }
  });
```

### Serialization
Gluino library provides a very nive abstractions for serialization and deserialization. In order to use those abstractions you need to implement the following interfaces for your platform:

1. IContextFactory - responsible for creating the serialization and deserialization contexts
* ISerializationContext - the context needed for serialization and contains methods like `setString`, `setInt` etc.
* IDeserializationContext - the context needed for deserialization and contains methods like `getString`, `getInt` etc.

In order to create a serializer for your object you need to inherit from `Seializer<T>` and implement `serializeImpl` and/or `deserializeImpl`.

```cpp
Core::Status
ColorSerializer::serializeImpl(ISerializationContext& context, const Color& status) const {
  auto result = context.setByte("red", color.getR());
  if (!result.isOk())
    return result;
  ... // Repeat for green and blue
  return Status::OK;
}

std::tuple<Core::Status, std::unique_ptr<Color>>
RequestSerializer::deserializeImpl(const IDeserializationContext& context) const {
  Status result;
  uint8_t r, g, b;
  std::tie(result, r) = context.getByte("r");
  if (!result.isOk())
    return std::make_tuple(result, nullptr);
  ... // Repeat for green and blue
  auto color = std::make_unique<Color>(r, g, b);
  return std::make_tuple(Status::OK, std::move(color));
}
```
