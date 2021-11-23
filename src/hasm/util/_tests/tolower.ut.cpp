#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "util/util.h"


TEST_SUITE_BEGIN("util-tolower");


TEST_CASE("should not modify original string") {
  std::string str = "Hello WOrld";

  CHECK_EQ("hello world", toLower(str));
  CHECK_EQ("Hello WOrld", str);

  str = "N&1";
  CHECK_EQ("n&1", toLower(str));
  CHECK_EQ("N&1", str);
}


TEST_SUITE_END();
