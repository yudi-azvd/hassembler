#include <iostream>
#include <vector>

#include "../lib/doctest/doctest.h"

struct LineAndItsTokens {
  std::string line;
  std::vector<std::string> tokens;

  friend std::ostream &operator<<(std::ostream& os, const LineAndItsTokens& line);

  friend std::ostream &operator<<(std::ostream& os, const LineAndItsTokens& line) {
    std::string tokens = "";
    for(auto token : line.tokens)
      tokens.append("\"" + token + "\", ");
    return os << "\"" << line.line << "\"" << ", {" << tokens << "}";
  }
};

std::vector<std::string> parseLine(std::string) {
  std::vector<std::string> tokens {"COPY", "SRC", "DST"};
  return tokens;
}

TEST_CASE("parse line") {
  std::string line;
  std::vector<std::string> expectedTokens;
  std::vector<std::string> gotTokens;

  std::vector<LineAndItsTokens> lineAndItsTokens {
    {"COPY SRC DST", {"COPY", "SRC", "DST"}},
    {"N2: SPACE", {"N2", "SPACE"}},
  };

  int i = 0;
  for (auto ln : lineAndItsTokens) {
    line = ln.line;
    expectedTokens = ln.tokens;
    gotTokens = parseLine(line);
    INFO(i++, ": ", ln);
    CHECK_EQ(gotTokens, expectedTokens);
  }
  
  CHECK("essa string" != "dessa outr string");
}