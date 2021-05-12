#include <iostream>
#include <vector>

#include "../../lib/doctest/doctest.h"
#include "../../src/ligador/definitionstable.hpp"

TEST_CASE("basic definitions table - addition and has") {
  DefinitionsTable table;

  table.add("name13", 13);

  CHECK(table.has("name13"));
  CHECK_FALSE(table.has("non-existing"));
}


TEST_CASE("definitions table - getPositionOf") {
    DefinitionsTable table;

  table.add("name13", 13);
  table.add("name200", 200);

  CHECK_EQ(table.getPositionOf("name13"), 13);
  CHECK_EQ(table.getPositionOf("name200"), 200);
}

