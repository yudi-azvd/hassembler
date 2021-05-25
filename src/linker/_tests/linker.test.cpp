#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "linker/linker.hpp"

TEST_CASE("basic linker") {
  Linker linker({"yudi"});

  CHECK_EQ(1, 1);
}
