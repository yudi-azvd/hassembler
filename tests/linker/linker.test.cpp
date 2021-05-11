#include <iostream>
#include <vector>

#include "../../lib/doctest/doctest.h"
#include "../../src/ligador/linker.hpp"

TEST_CASE("basic linker") {
  Linker linker({"yudi"});

  CHECK_EQ(1, 1);
}
