#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "assembler/line.h"


TEST_SUITE_BEGIN("assembler-line");


TEST_CASE("simple line") {
  Line line = "this line";
  CHECK(line.getContent() == "this line");
}


TEST_CASE("vector of lines") {
  std::vector<Line> lines = {
    "line 1",
    "line 2",
    "line 3",
  };

  CHECK(lines[0].getContent() == "line 1");
  CHECK(lines[1].getContent() == "line 2");
  CHECK(lines[2].getContent() == "line 3");
}


TEST_CASE("vector of const char* ") {

  std::vector<const char*> lines = {
    "line 1",
    "line 2",
    "line 3",
  };

  std::vector<Line> linesVector(lines.begin(), lines.end());

  CHECK(linesVector[0].getContent() == "line 1");
  CHECK(linesVector[1].getContent() == "line 2");
  CHECK(linesVector[2].getContent() == "line 3");
}


TEST_SUITE_END();
