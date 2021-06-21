#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "util/symbolstable.h"


TEST_SUITE("util-symbolstable") {

TEST_CASE("should add symbol") {
  SymbolsTable table;

  table.add("symbol", 10);
  CHECK(table.getPositionOf("symbol") == 10);
}


TEST_CASE("should not create symbol trying to access non existing symbol") {
  SymbolsTable table;

  CHECK_FALSE(table.has("non-existing"));
  CHECK_FALSE(table.has("non-existing"));
  CHECK_THROWS_AS(table.getPositionOf("non-existing"), std::out_of_range);
}


TEST_CASE("should add external symbol") {
  SymbolsTable table;

  table.add("external-symbol", 5, true);

  CHECK(table.isExternal("external-symbol"));
}

}
