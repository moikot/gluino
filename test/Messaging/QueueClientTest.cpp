#include "catch.hpp"
#include "fakeit.hpp"

#include "Messaging/QueueClient.hpp"
#include "Messaging/IMessageQueue.hpp"

using namespace Messaging;
using namespace fakeit;

TEST_CASE("QueueClient can be constructed", "[QueueClient]") {

  Mock<IMessageQueue> messageQueue;
  auto client = QueueClient::makeUnique("id", messageQueue.get());

  SECTION("identifier retained") {
    REQUIRE(client->getId() == "id");
  }

}
