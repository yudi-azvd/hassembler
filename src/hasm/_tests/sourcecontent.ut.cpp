#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "hasm/sourcecontent.h"


TEST_CASE("asasas simple line") {
  SourceContent content = {{
    "line one",
    "line two",
  }};

  CHECK(content.getLines()[0].getContent() == "line one");
  CHECK(content.getLines()[1].getContent() == "line two");
}
