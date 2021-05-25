#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "linker/linker.hpp"
#include "assembler/util.h"

TEST_CASE("basic object code alignment") {
  std::vector<int> gotFinalObjectCode;
  std::vector<int> expFinalObjectCode = {
    0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3
  };
  std::vector<std::vector<int>> o;
  std::vector<std::vector<int>> objectCodes = {
    {0, 1, 2, 3},
    {0, 1, 2, 3},
    {0, 1, 2, 3},
  };

  Linker linker({"arq1"});

  gotFinalObjectCode = linker.alignObjectCodes(objectCodes);
  INFO("exp", expFinalObjectCode);
  INFO("got", gotFinalObjectCode);
  CHECK_EQ(expFinalObjectCode, gotFinalObjectCode);
}
