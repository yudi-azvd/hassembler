#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "assembler/twopasses/zerothpass.h"
#include "assembler/scanner/scanner.h"
#include "util/util.h"


TEST_CASE("should detect data section coming in first") {
  Source source = {{
    "section data",
    "section text",
  }};

  ZerothPass zerothPass(source);
  zerothPass.run();

  CHECK_EQ(2, source.getTextSectionLine());
  CHECK_EQ(1, source.getDataSectionLine());
  CHECK(source.dataSectionComesFirst());
}


TEST_CASE("should detect data section coming in second") {
  Source source = {{
    "section text",
    "section data",
  }};

  ZerothPass zerothPass(source);
  zerothPass.run();

  CHECK_EQ(1, source.getTextSectionLine());
  CHECK_EQ(2, source.getDataSectionLine());
  CHECK_FALSE(source.dataSectionComesFirst());
}


TEST_CASE("should detect sections with lines extra lines") {
  Source source = {{
    "section text",
    "output n1",
    "",
    "section data", // linha 4!
    "n1: const 3"
  }};

  ZerothPass zerothPass(source);
  zerothPass.run();

  CHECK_EQ(1, source.getTextSectionLine());
  CHECK_EQ(4, source.getDataSectionLine());
  CHECK_FALSE(source.dataSectionComesFirst());
}


TEST_CASE("should detect sections with lines extra lines - inverted") {
  Source source = {{
    "section data",
    "n1: const 3",
    "section text", // linha 3!
    "",
    "output n1",
  }};

  ZerothPass zerothPass(source);
  zerothPass.run();

  CHECK_EQ(3, source.getTextSectionLine());
  CHECK_EQ(1, source.getDataSectionLine());
  CHECK(source.dataSectionComesFirst());
}
