#include <iostream>
#include <vector>

#include "../../lib/doctest/doctest.h"
#include "../../include/util.h"

TEST_CASE("lowercaser") {
  std::vector<std::string> strs = {
    "Hello WOrld", "APPLE", "ANOTHER STring"};

  std::vector<std::string> gotLowered = stringVectorLowerCased(strs);
  std::vector<std::string> expectedLowered = {
    "hello world", "apple", "another string"};

  CHECK_EQ(expectedLowered, gotLowered);
}


TEST_CASE("lowercaser should not modify original string") {
  std::vector<std::string> strs = {
    "Hello WOrld", "APPLE", "ANOTHER STring"};

  std::vector<std::string> gotLowered = stringVectorLowerCased(strs);

  CHECK_NE(strs, gotLowered);
}
