#include <iostream>
#include <vector>

#include "doctest/doctest.h"


void useless_for() {
  size_t i;
  for (i = 0; i < 100; i++) {
    ++i;
  }
  std::cout << i << std::endl;
}


TEST_CASE("vectors can be sized and resized") {
  std::vector<int> v(5);

  REQUIRE(v.size() == 5);
  REQUIRE(v.capacity() >= 5);

  SUBCASE("adding to the vector increases it's size") {
    v.push_back(1);

    useless_for();

    CHECK(v.size() == 6);
    CHECK(v.capacity() >= 6);
  }

  SUBCASE("reserving increases just the capacity") {
    v.reserve(6);

    useless_for();
    CHECK(v.size() == 5);
    CHECK(v.capacity() >= 6);
  }
}
