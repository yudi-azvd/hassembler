#include <iostream>
#include <vector>

#include "../../lib/doctest/doctest.h"

#include "../../include/parseline.h"
#include "../../include/assembler.h"


// TEST_CASE("parse line, dummy") {
//   std::string line;
//   std::vector<std::string> expectedTokens;
//   std::vector<std::string> gotTokens;

//   Assembler as;

//   std::vector<LineAndItsTokens> lineAndItsTokens {
//     {"COPY SRC DST", {"COPY", "SRC", "DST"}},
//     {"N2: SPACE", {"N2", "SPACE"}},
//   };

//   int i = 0;
//   for (auto ln : lineAndItsTokens) {
//     line = ln.line;
//     expectedTokens = ln.tokens;
//     gotTokens = as.parseLine(line);
//     INFO(i++, ": ", ln);
//     CHECK_EQ(gotTokens, expectedTokens);
//   }
// }


TEST_CASE("parse line") {
  std::string line;
  std::vector<std::string> expectedTokens;
  std::vector<std::string> gotTokens;

  Assembler as;

  std::vector<LineAndItsTokens> lineAndItsTokens {
    {"N2: SPACE", {"N2", "SPACE"}},
  };

  gotTokens = as.parseLine(lineAndItsTokens[0].line);
  
  CHECK_EQ(gotTokens[0], "N2");
}
