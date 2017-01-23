#include "MessageQueue.hpp"

#include "Core/Casting.hpp"

using namespace Core;
using namespace Messaging;

namespace {
  static const std::string messageQueueSenderId = "messageQueue";
}

MessageQueue::MessageQueue(ILogger::Shared logger): logger(logger) {
}

void
MessageQueue::idle() {
  while (!requests.empty())
  {
    auto request = requests.front();
    requests.pop();
    processRequest(*request);
  }
  while (!responses.empty())
  {
    auto response = responses.front();
    responses.pop();
    processResponse(*response);
  }
  while (!events.empty()) {
    auto event = events.front();
    events.pop();
    processEvent(*event);
  }
}

Status
MessageQueue::addRequest(Request::Shared request) {
  requests.push(request);
  return Status::OK;
}

Status
MessageQueue::addEvent(Event::Shared event) {
  events.push(event);
  return Status::OK;
}

QueueGenericClient::Shared
MessageQueue::createClient(std::string clientId) {
  auto client = QueueGenericClient::makeShared(clientId, *this);
  clients.push_back(client);
  return client;
}

QueueResourceClient::Shared
MessageQueue::createClient(std::string clientId, std::string resource) {
  auto client = QueueResourceClient::makeShared(clientId, resource, *this);
  clients.push_back(client);
  return client;
}

void
MessageQueue::removeClient(QueueClient::Shared client) {
  clients.remove(client);
}

QueueResourceController::Shared
MessageQueue::createController(std::string resource) {
  auto controller = QueueResourceController::makeShared(resource, *this);
  controllers.push_back(controller);
  return controller;
}

void
MessageQueue::removeController(QueueResourceController::Shared controller) {
  controllers.remove(controller);
}

void
MessageQueue::processRequest(const Request& request) {
  logger->message("Processing a request from '" + request.getSender() + "'");
  IEntity::Unique result;
  auto handler = getRequestHandler(request);
  if (handler) {
    result = handler(request);
  } else {
    logger->error("Unable to find a request handler.");
    result = Status::makeUnique(StatusCode::NotFound, "Unable to find a request handler.");
  }
  sendResponseFor(request, std::move(result));
}

void
MessageQueue::processResponse(const Response& response) {
  auto receiver = response.getReceiver();
  logger->message("Processing a response to '" + receiver + "'");
  auto client = getClient(receiver);
  if (client) {
    client->onResponse(response);
  } else {
    logger->error("Unable to find client '" + receiver + "'");
  }
}

void
MessageQueue::processEvent(const Event& event) {
  logger->message("Broadcasting event '" + event.getEventType() + "'.");
  std::list<QueueClient::Shared> deletedClients;
  for(auto& client: clients) {
    if (client.use_count() != 1) {
	    client->onEvent(event);
    } else {
      deletedClients.push_back(client);
    }
  }
  for(auto client: deletedClients) {
    clients.remove(client);
  }
}

QueueClient::Shared
MessageQueue::getClient(std::string clientId) {
  for (auto& client : clients) {
    if (client->getClientId() == clientId) {
      if (client.use_count() == 1) {
        clients.remove(client);
        return nullptr;
      }
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
      if (controller.use_count() == 1) {
        controllers.remove(controller);
        return nullptr;
      }
      return handler;
    }
  }
  return nullptr;
}

void
MessageQueue::sendResponseFor(const Request& request, IEntity::Unique result) {
  auto response = Response::makeShared(
          request.getRequestType(),
          request.getSender(),
          request.getResource(),
          std::move(result)
         );

  responses.push(response);
}
