#include <iostream>
#include <vector>

#include "../../lib/doctest/doctest.h"

#include "../../include/errors.h"
#include "../../include/parseline.h"
#include "../../include/assembler.h"


TEST_CASE("findLabel") {
  std::string gotLabel;
  std::string expectedLabel;

  Assembler as;

  gotLabel = as.findLabel("COPY SRC DST");
  expectedLabel = "";
  CHECK_EQ(gotLabel, expectedLabel);

  gotLabel = as.findLabel("COPY NEW_DATA,OLD_DATA");
  expectedLabel = "";
  CHECK_EQ(gotLabel, expectedLabel);

  gotLabel = as.findLabel("N2: SPACE");
  expectedLabel = "N2";
  CHECK_EQ(gotLabel, expectedLabel);

  gotLabel = as.findLabel("N2: CONST 2");
  expectedLabel = "N2";
  CHECK_EQ(gotLabel, expectedLabel);

  gotLabel = as.findLabel("NEW_DATA: SPACE");
  expectedLabel = "NEW_DATA";
  CHECK_EQ(gotLabel, expectedLabel);

  gotLabel = as.findLabel("__LABL: SPACE");
  expectedLabel = "__LABL";
  CHECK_EQ(gotLabel, expectedLabel);

  CHECK_THROWS_WITH_AS(
    as.findLabel("2n2: const: 2"), 
    "invalid label: 2n2",
    LexicalError
  );

  CHECK_THROWS_WITH_AS(
    as.findLabel("&N2: CONST 2"), 
    "invalid label: &N2",
    LexicalError
  );

  CHECK_THROWS_WITH_AS(
    as.findLabel("N&2: CONST 2"), 
    "invalid label: N&2",
    LexicalError
  );
}
