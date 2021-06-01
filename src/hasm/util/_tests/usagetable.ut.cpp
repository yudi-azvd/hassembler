#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "util/usagetable.h"


TEST_SUITE_BEGIN("util-usagetable");


TEST_CASE("basic usage table - has") {
  UsageTable table;

  table.add("name1",  9);

  CHECK(table.has("name1"));
  CHECK_FALSE(table.has("non-existing"));
}


TEST_CASE("usage table - getPositionOf") {
  UsageTable table;

  table.add("name1",  9);
  table.add("name13",  13);

  CHECK(table.has("name1"));
  CHECK_EQ(table.getPositionOf("name1"), 9);
  CHECK_EQ(table.getPositionOf("name13"), 13);
}

