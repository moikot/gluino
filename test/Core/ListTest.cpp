#include "Utils/Testing.hpp"

#include "Core/List.hpp"
#include "Core/Memory.hpp"

using namespace Core;

namespace {
  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
    public:
      explicit Content(int i):i(i) {}
      int i;
  };

  class ContentList : public Core::List<Content> {
    TYPE_INFO(ContentList, Core::List<Content>, "contentList")
  };

}

TEST_CASE("can add IEntity", "[List]") {
  ContentList list;

  list.addEntity(Content(1));
  list.addEntity(Content(10));
  int acc = 0;

  auto res = list.forEachEntity([&](const IEntity& element) {
    acc += static_cast<const Content&>(element).i;
    return Status::OK;
  });

  REQUIRE(acc == 11);
  REQUIRE(res.getStatusCode() == StatusCode::OK);
}

TEST_CASE("can add Content", "[List]") {
  ContentList list;

  list.add(Content(1));
  list.add(Content(10));
  int acc = 0;

  auto res = list.forEach([&](const Content& element) {
    acc += element.i;
    return Status::OK;
  });

  REQUIRE(acc == 11);
  REQUIRE(res.getStatusCode() == StatusCode::OK);
}

TEST_CASE("can abort forEach", "[List]") {
  ContentList list;

  list.add(Content(1));
  list.add(Content(10));
  list.add(Content(100));
  int acc = 0;

  auto res = list.forEach([&](const Content& element) {
    if (element.i > 10)
      return Status(StatusCode::NotFound, "not found");
    acc += element.i;
    return Status::OK;
  });

  REQUIRE(acc == 11);
  REQUIRE(res.getStatusCode() == StatusCode::NotFound);
}
