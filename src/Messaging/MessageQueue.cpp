#include "MessageQueue.hpp"

#include "Core/Casting.hpp"
#include "Core/Logger.hpp"

using namespace Core;
using namespace Messaging;

namespace {
  static const std::string messageQueueSenderId = "messageQueue";
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

StatusResult::Unique
MessageQueue::addRequest(Request::Shared request) {
  requests.push(request);
  return StatusResult::OK();
}

StatusResult::Unique
MessageQueue::addEvent(Event::Shared event) {
  events.push(event);
  return StatusResult::OK();
}

QueueClient::Shared
MessageQueue::createClient(std::string clientId) {
  auto client = QueueClient::makeShared(clientId, *this);
  clients.push_back(client);
  return client;
}

QueueController::Shared
MessageQueue::createController() {
  auto controller = QueueController::makeShared(*this);
  controllers.push_back(controller);
  return controller;
}

void
MessageQueue::removeClient(QueueClient::Shared client) {
  clients.remove(client);
}

void
MessageQueue::removeController(QueueController::Shared controller) {
  controllers.remove(controller);
}

void
MessageQueue::processRequest(const Request& request) {
  Logger::message("Processing a request from '" + request.getSender() + "'");
  IEntity::Unique result;
  auto handler = getRequestHandler(request);
  if (handler) {
    result = handler(request);
  } else {
    Logger::error("Unable to find a request handler.");
    result = StatusResult::makeUnique(StatusCode::NotFound, "Unable to find a request handler.");
  }
  sendResponseFor(request, std::move(result));
}

void
MessageQueue::processResponse(const Response& response) {
  auto receiver = response.getReceiver();
  Logger::message("Processing a response to '" + receiver + "'");
  auto client = getClient(receiver);
  if (client) {
    client->onResponse(response);
  } else {
    Logger::error("Unable to find client '" + receiver + "'");
  }
}

void
MessageQueue::processEvent(const Event& event) {
  Logger::message("Broadcating event '" + event.getEventType() + "'.");
  std::list<QueueClient::Shared> deletedClients;
  for(auto client: clients) {
    if (!client.unique()) {
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
  QueueClient::Shared queueClient;
  for(auto client: clients) {
    if (client->getId() == clientId) {
      queueClient = client;
      break;
    }
  }
  if (queueClient && queueClient.unique()) {
    clients.remove(queueClient);
    return nullptr;
  }
  return queueClient;
}

RequestFunction
MessageQueue::getRequestHandler(const Request& request) {
  RequestFunction func;
  QueueController::Shared queueController;
  for(auto controller: controllers) {
    func = controller->getRequestHandler(request);
    if (func) {
      queueController = controller;
      break;
    }
  }
  if (queueController && queueController.unique()) {
    controllers.remove(queueController);
    return nullptr;
  }
  return func;
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
