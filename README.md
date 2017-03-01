# Gluino
[![Build Status](https://api.travis-ci.org/anisimovsergey/gluino.svg?branch=master)](https://travis-ci.org/anisimovsergey/gluino?branch=master)
[![Build status](https://ci.appveyor.com/api/projects/status/oiyjkkvbiyfy2u0h?svg=true)](https://ci.appveyor.com/project/anisimovsergey/gluino)
[![Coverage Status](https://coveralls.io/repos/github/anisimovsergey/gluino/badge.svg?branch=master)](https://coveralls.io/github/anisimovsergey/gluino?branch=master)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/74ecfbf675f34a3192ee0894ba75043e)](https://www.codacy.com/app/anisimovsergey/gluino?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=anisimovsergey/gluino&amp;utm_campaign=Badge_Grade)

## The message queue

All the messages in the system are divided into three types: requests, responses and events.
All the messages are added to the message queue and processed in FIFO order.
All the messages added into the queue are processed in the following priority: requests, responses, events.

### Request
The request message (Request class) is send by resource clients (QueueResourceClient class) handled by resource controllers (QueueResourceController class). Every request should contain the following information:

1. Sender - the unique client id for routing the request processing result (response) back to the sender
* Resource - the unique id of the resource the request is made for
* Request type - the type of the operation to perform with the resource
* Content (optional) - the payload for the request

For example:
```cpp
  auto connection = std::make_unique<ConnectionParams>("WIFI_NAME", "PASSWORD");
  auto request = std::make_unique<Request>("clientId", RequestType::Create, "connection", std::move(connection));
```

### Response
The response message (Response class) is sent by queue resource controllers (QueueResourceController class) in the result of handling a request sent by a resource client (QueueResourceClient class). Every response should contain the following information:

1. Request type - the type of the request the response corresponds to
* Receiver - the original request sender becomes the receiver of the response
* Resource - the unique id of the resource the original request was made for
* Content (optional) - the payload for the response

For example:
```cpp
  auto status = std::make_unique<Status>(StatusCode::Created, "The connection was created.");
  auto response = std::make_unique<Response>("clientId", RequestType::Create, "connection", std::move(status));
```

### Events
The event message (Event class) is sent by queue resource controllers (QueueResourceController class) in order to notify all the queue resource clients abut some changes in a resource state. Every event should contain the following information:

1. Event type - the type of the event
* Resource - the unique id of the resource the event associated with
* Content (optional) - the payload for the event

```cpp
  auto connection = std::make_unique<Connection>("WIFI_NAME", isConnected);
  auto event = std::make_unique<Event>(EventType::Createed, "connection", std::move(connection));
```
