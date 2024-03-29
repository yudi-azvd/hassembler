#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "util/util.h"

TEST_CASE("should find in vector") {
  std::vector<std::string> strs = {
    "Hello WOrld", "APPLE", "ANOTHER STring"};

  CHECK(findInVector(strs, "APPLE"));
}


TEST_CASE("should not find in vector") {
  std::vector<std::string> strs = {
    "Hello WOrld", "APPLE", "ANOTHER STring"};

  CHECK_FALSE(findInVector(strs, "non-existing"));
}
