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
2. Resource - the unique id of the resource the request is made for
3. Request type - the type of the operation to perform with the resource
4. Content (optional) - the payload for the request

For example:
```cpp
  auto connection = std::make_unique<ConnectionParams>("WIFI_NAME", "PASSWORD");
  Request("clientId", RequestType::Create, "connection", std::move(connection));
```

### Response
The response message (Response class) is sent by queue resource controllers (QueueResourceController class) in the result of handling a request sent by a resource client (QueueResourceClient class). Every response should contain the following information:
1. Request type - the type of the request the response corresponds to
2. Receiver - the original request sender becomes the receiver of the response
3. Resource - the unique id of the resource the original request was made for
4. Content (optional) - the payload for the response

For example:
```cpp
  auto status = std::make_unique<Status>(StatusCode::Created, "The connection was created.");
  Response("clientId", RequestType::Create, "connection", std::move(status));
```
