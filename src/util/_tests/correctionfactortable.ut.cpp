#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "linker/linker.hpp"
#include "util/correctionfactortable.hpp"

#include "util/util.h"

TEST_CASE("basic code alignment") {
  CorrectionFactorTable table;

  table.add("mod_a", 4);
  table.add("mod_b", 5);
  table.add("mod_c", 6);

  CHECK_EQ(table.getSizeOf("mod_a"), 0);
  CHECK_EQ(table.getSizeOf("mod_b"), 4);
  CHECK_EQ(table.getSizeOf("mod_c"), 9);
}


TEST_CASE("real alignment example") {
  CorrectionFactorTable table;

  table.add("mod_a", 22);
  table.add("mod_b", 49);
  table.add("mod_c", 72);

  CHECK_EQ(table.getSizeOf("mod_a"), 0);
  CHECK_EQ(table.getSizeOf("mod_b"), 22);
  CHECK_EQ(table.getSizeOf("mod_c"), 71);
}
