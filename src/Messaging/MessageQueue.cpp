#include "MessageQueue.hpp"

#include "Core/Memory.hpp"

using namespace Core;
using namespace Messaging;

MessageQueue::MessageQueue(ILogger& logger): logger(logger) {
}

void
MessageQueue::idle() {
  while (!requests.empty())
  {
    auto& request = requests.front();
    processRequest(*request);
    requests.pop();
  }
  while (!responses.empty())
  {
    auto& response = responses.front();
    processResponse(*response);
    responses.pop();
  }
  while (!events.empty()) {
    auto& event = events.front();
    processEvent(*event);
    events.pop();
  }
}

Status
MessageQueue::addRequest(std::unique_ptr<Request> request) {
  requests.emplace(std::move(request));
  return Status::OK;
}

Status
MessageQueue::addEvent(std::unique_ptr<Event> event) {
  events.emplace(std::move(event));
  return Status::OK;
}

std::unique_ptr<QueueGenericClient>
MessageQueue::createClient(std::string clientId) {
  auto client = std::make_unique<QueueGenericClient>(clientId, *this);
  clients.push_back(client.get());
  return client;
}

std::unique_ptr<QueueResourceClient>
MessageQueue::createClient(std::string clientId, std::string resource) {
  auto client = std::make_unique<QueueResourceClient>(clientId, resource, *this);
  clients.push_back(client.get());
  return client;
}

void
MessageQueue::removeClient(const QueueClient& client) {
  clients.remove(&client);
}

std::unique_ptr<QueueResourceController>
MessageQueue::createController(std::string resource) {
  auto controller = std::make_unique<QueueResourceController>(resource, *this);
  controllers.push_back(controller.get());
  return controller;
}

void
MessageQueue::removeController(const QueueResourceController& controller) {
  controllers.remove(&controller);
}

void
MessageQueue::processRequest(const Request& request) {
  logger.message("Processing a request from '" + request.getSender() + "'");
  std::unique_ptr<IEntity> result;
  auto handler = getRequestHandler(request);
  if (handler) {
    result = handler(request);
  } else {
    logger.error("Unable to find a request handler.");
    result = std::make_unique<Status>(StatusCode::NotFound, "Unable to find a request handler.");
  }
  sendResponseFor(request, std::move(result));
}

void
MessageQueue::processResponse(const Response& response) {
  auto receiver = response.getReceiver();
  logger.message("Processing a response to '" + receiver + "'");
  auto client = getClient(receiver);
  if (client) {
    client->onResponse(response);
  } else {
    logger.error("Unable to find client '" + receiver + "'");
  }
}

void
MessageQueue::processEvent(const Event& event) {
  logger.message("Broadcasting event '" + event.getEventType() + "'.");
  for(auto client: clients) {
	  client->onEvent(event);
  }
}

const QueueClient*
MessageQueue::getClient(std::string clientId) {
  for (auto& client : clients) {
    if (client->getClientId() == clientId) {
      return client;
    }
  }
  return nullptr;
}

RequestHandler
MessageQueue::getRequestHandler(const Request& request) {
  for(auto& controller: controllers) {
    auto handler = controller->getRequestHandler(request);
    if (handler) {
      return handler;
    }
  }
  return nullptr;
}

void
MessageQueue::sendResponseFor(const Request& request, std::unique_ptr<IEntity> result) {
  auto response = std::make_unique<Response>(
		  request.getSender(),
          request.getRequestType(),
          request.getResource(),
          std::move(result)
         );

  responses.emplace(std::move(response));
}
