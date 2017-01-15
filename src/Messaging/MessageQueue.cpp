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
MessageQueue::addResponse(Response::Shared response) {
  responses.push(response);
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
MessageQueue::createController(std::string controllerId) {
  auto controller = QueueController::makeShared(controllerId, *this);
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
  auto controller = getController(request);
  if (controller) {
    result = controller->processRequest(request);
  } else {
    Logger::error("Unable to find a controller.");
    result = StatusResult::makeUnique(StatusCode::NotFound, "Unable to find a controller.");
  }
  sendResponseFor(request, std::move(result), controller.get());
}

void
MessageQueue::processResponse(const Response& response) {
  auto sender = response.getSender();
  auto receiver = response.getReceiver();
  Logger::message("Processing a response from '" + sender + "' to '" + receiver + "'");
  auto client = getClient(receiver);
  if (client) {
    client->onResponse(response);
  } else {
    Logger::error("Unable to find client '" + receiver + "'");
  }
}

void
MessageQueue::processEvent(const Event& event) {
  auto sender = event.getSender();
  Logger::message("Broadcating a notification from '" + sender + "'.");
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

QueueController::Shared
MessageQueue::getController(const Request& request) {
  QueueController::Shared queueController;
  for(auto controller: controllers) {
    if (controller->canProcessRequest(request)) {
      queueController = controller;
      break;
    }
  }
  if (queueController && queueController.unique()) {
    controllers.remove(queueController);
    return nullptr;
  }
  return queueController;
}

void
MessageQueue::sendResponseFor(const Request& request,
  IEntity::Unique result, const QueueController* controller) {

  std::string sender(messageQueueSenderId);
  if (controller)
    sender = controller->getId();

  auto response = Response::makeShared(
          sender,
          request.getSender(),
          request.getActionType(),
          request.getResource(),
          std::move(result)
         );

  responses.push(response);
}
