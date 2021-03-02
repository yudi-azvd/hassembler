#include <iostream>
#include <vector>

#include "../../lib/doctest/doctest.h"

#include "../../include/parseline.h"


TEST_CASE("findLabel") {
  std::string gotLabel;
  std::string expectedLabel;

  std::vector<std::string> lines {
    {"COPY SRC DST"},
    {"N2: SPACE"},
  };

  gotLabel = findLabel("COPY SRC DST");
  expectedLabel = "";
  CHECK_EQ(gotLabel, expectedLabel);

  gotLabel = findLabel("N2: SPACE");
  expectedLabel = "N2";
  CHECK_EQ(gotLabel, expectedLabel);

  gotLabel = findLabel("N2: CONST 2");
  expectedLabel = "N2";
  CHECK_EQ(gotLabel, expectedLabel);

  gotLabel = findLabel("N2: CONST: 2");
  expectedLabel = "N2";
  CHECK_EQ(gotLabel, expectedLabel);
}
