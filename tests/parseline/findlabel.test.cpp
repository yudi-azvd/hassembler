#include <iostream>
#include <vector>

#include "../../lib/doctest/doctest.h"

#include "../../include/errors.h"
#include "../../include/parseline.h"


TEST_CASE("findLabel") {
  std::string gotLabel;
  std::string expectedLabel;

  gotLabel = findLabel("COPY SRC DST");
  expectedLabel = "";
  CHECK_EQ(gotLabel, expectedLabel);

  gotLabel = findLabel("COPY NEW_DATA, OLD_DATA");
  expectedLabel = "";
  CHECK_EQ(gotLabel, expectedLabel);

  gotLabel = findLabel("N2: SPACE");
  expectedLabel = "N2";
  CHECK_EQ(gotLabel, expectedLabel);

  gotLabel = findLabel("N2: CONST 2");
  expectedLabel = "N2";
  CHECK_EQ(gotLabel, expectedLabel);

  gotLabel = findLabel("NEW_DATA: SPACE");
  expectedLabel = "NEW_DATA";
  CHECK_EQ(gotLabel, expectedLabel);

  gotLabel = findLabel("__LABL: SPACE");
  expectedLabel = "__LABL";
  CHECK_EQ(gotLabel, expectedLabel);

  CHECK_THROWS_WITH_AS(
    findLabel("2N2: CONST: 2"), 
    "invalid label: 2N2",
    LexicalError
  );

  CHECK_THROWS_WITH_AS(
    findLabel("&N2: CONST 2"), 
    "invalid label: &N2",
    LexicalError
  );

  CHECK_THROWS_WITH_AS(
    findLabel("N&2: CONST 2"), 
    "invalid label: N&2",
    LexicalError
  );
}
