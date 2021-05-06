#include <iostream>
#include <vector>

#include "../../lib/doctest/doctest.h"
#include "../../src/montador/assembler.h"
#include "../../src/montador/util.h"


TEST_CASE("parseLine") {
  std::string line;
  std::vector<std::string> expectedTokens;
  std::vector<std::string> gotTokens;

  Assembler as;

  std::vector<LineAndItsTokens> linesAndItsExpectedTokens {
    {"N2: SPACE", {"N2", ":", "SPACE"}},
    {"COPY    NEW_DATA,OLD_DATA", {"COPY", "NEW_DATA", ",", "OLD_DATA"}},
    {"TMP_DATA: SPACE", {"TMP_DATA", ":", "SPACE"}},
    {"TMP_DATA\t:SPACE", {"TMP_DATA", ":", "SPACE"}},
    {"TMP_DATA\t:\tSPACE", {"TMP_DATA", ":", "SPACE"}},
    {"DOIS: CONST 2", {"DOIS", ":", "CONST", "2"}},
    {"L1: DIV DOIS", {"L1", ":", "DIV", "DOIS"}}
  };

  int i = 0;
  for (auto lineExpectedTokens : linesAndItsExpectedTokens) {
    line = lineExpectedTokens.line;
    expectedTokens = lineExpectedTokens.tokens;

    gotTokens = as.parseLine(line);
    INFO(i, ": [", line, "]");
    INFO(i++, ": [", vectorToString(gotTokens), "]");
    CHECK_EQ(gotTokens, expectedTokens);
  }
}
