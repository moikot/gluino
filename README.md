# Gluino
[![Build Status](https://api.travis-ci.org/anisimovsergey/gluino.svg?branch=master)](https://travis-ci.org/anisimovsergey/gluino?branch=master)
[![Build status](https://ci.appveyor.com/api/projects/status/oiyjkkvbiyfy2u0h?svg=true)](https://ci.appveyor.com/project/anisimovsergey/gluino)
[![Coverage Status](https://coveralls.io/repos/github/anisimovsergey/gluino/badge.svg?branch=master)](https://coveralls.io/github/anisimovsergey/gluino?branch=master)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/74ecfbf675f34a3192ee0894ba75043e)](https://www.codacy.com/app/anisimovsergey/gluino?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=anisimovsergey/gluino&amp;utm_campaign=Badge_Grade)

# Messaging

Messaging namespace contains a very basic implementation of the message processing with three major parts.

## The message queue

All the messages in the system are divided into three types: requests, responses and events.
All the messages are added to the message queue and processed in FIFO order.
All the messages added into the queue are processed in the following order: requests, responses, events.

### Request
The request message (Request class) is send by queue clients and should contain the following fields:
1. Sender - the unique client id for routing the result of the request processing back to the sender
2. Resource - the unique id of the resource the request is made for
3. Request type - the type of the operation to perform with the resource
4. Content - an optional payload for the operation specified in the request type

For example:
```cpp
  Request("create", "clientId", "connection", ConnectionParams::makeShared("WIFI_NAME", "PASSWORD"))
```

### Response
The response message (Response class) is sent by queue controller in the result of handling a request. Every response contains the following information:
1. Request type - the type of the request the response corresponds to
2. Receiver - the request sender becomes the receiver of the response
3. Resource - the unique id of the resource the original request was made for
4. Content - the payload of the response.

### Event
The event message (Event class) is send by queue controller


## The message queue client

## The message queue controller

## Internal message processing

When a service sends a `request` message it has to specify itself as the `sender`. In this way `receiver` field is automatically populated when the service which processes a `request` creates a `unicast` `response` or `notification` message.

The message queue processing (message pump):
1. The message is crated by a service and added to the message queue.
2. All the services with the message handler registered in the message pump are sequentially notified about the new message in the queue.
3. If a service can process the message it does the processing and returns the result of the processing to the message pump.
4. If the message is a unicast message the message gets removed from the queue and the result of the processing is added into it in a form of a response message.
5. If the message is a multicast message the message is not removed from the queue so the next service can get a chance to process it.
6. When all the services are requested to process the message and message is still in the queue, it gets removed automatically at the end of a message pump loop cycle.
7. If the message queue contains another message the message pumping cycle repeats.
