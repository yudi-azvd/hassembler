#include <iostream>
#include <vector>

#include "../../lib/doctest/doctest.h"
#include "../../include/assembler.h"
#include "../../include/util.h"

TEST_CASE("adjust object code") {
  std::map<std::string, int> expectedSymbolTable = {
    {"front", 10},
    {"final", 30},
    {"zero", 33},
    {"one", 34},
    {"older", 35},
    {"old", 36},
    {"new", 37},
    {"limit", 38},
  };

  std::vector<std::string> sourceFileContent = {
    "section data",
    "ZERO:   CONST 0",
    "ONE:    CONST 1",
    "OLDER:  SPACE",
    "OLD:    SPACE",
    "NEW:    SPACE",
    "LIMIT:  SPACE",
    "section text",
    "        COPY ZERO,OLDER",
    "        COPY ONE,OLD",
    "        INPUT LIMIT",
    "        OUTPUT OLD",
    "FRONT:  LOAD OLDER",
    "        ADD OLD",
    "        STORE NEW",
    "        SUB LIMIT",
    "        JMPP FINAL",
    "        OUTPUT NEW",
    "        COPY OLD,OLDER",
    "        COPY NEW,OLD",
    "        JMP FRONT",
    "FINAL:  OUTPUT LIMIT",
    "        STOP",
  };

  Assembler as;

  as.setSourceFileContent(sourceFileContent);
  as.runZerothPass();
  as.runFirstPass();
  as.adjustForDataSection();
  as.runSecondPass();
  as.adjustObjectCode(); // isso que é o texto de verdade.

  auto gotObjectCode = as.objectCode();
  std::vector<int> expectedObjectCode = {
    9, 33, 35, 9, 34, 36, 12, 38, 13, 36, 10, 35, 1, 36, 11, 37, 2, 38, 7, 30, 
    13, 37, 9, 36, 35, 9, 37, 36, 5, 10, 13, 38, 14, 0, 1, 0, 0, 0, 0
  };

  INFO("exp: ", vectorToString(expectedObjectCode));
  INFO("got: ", vectorToString(gotObjectCode));
  INFO("got: ", strToIntMapToString(expectedSymbolTable));
  INFO("got: ", strToIntMapToString(as.symbolTable()));

  CHECK_EQ(gotObjectCode, expectedObjectCode);
  CHECK_EQ(as.symbolTable(), expectedSymbolTable);
}


TEST_CASE("adjust object code") {
  std::map<std::string, int> expectedSymbolTable = {
    {"fat", 4},
    {"fim", 18},
    {"aux", 21},
    {"n", 22},
    {"one", 23},
  };

  std::vector<std::string> sourceFileContent = {
    "section data",
    "aux:    space",
    "n:      space",
    "one:    const 1",
    "section text",
    "        input n",
    "        load n",
    "fat:    sub one",
    "        jmpz fim",
    "        store aux",
    "        mul n",
    "        store n",
    "        load aux",
    "        jmp fat",
    "fim:    output n",
    "        stop",
  };

  Assembler as;

  as.setSourceFileContent(sourceFileContent);
  as.runZerothPass();
  as.runFirstPass();
  as.adjustForDataSection();
  as.runSecondPass();
  as.adjustObjectCode(); // isso que é o texto de verdade.

  auto gotObjectCode = as.objectCode();
  std::vector<int> expectedObjectCode = {
    12, 22, 10, 22, 2, 23, 8, 18, 11, 21, 3, 
    22, 11, 22, 10, 21, 5, 4, 13, 22, 14, 0, 0, 1
  };

  INFO("exp: ", vectorToString(expectedObjectCode));
  INFO("got: ", vectorToString(gotObjectCode));
  INFO("got: ", strToIntMapToString(expectedSymbolTable));
  INFO("got: ", strToIntMapToString(as.symbolTable()));

  CHECK_EQ(gotObjectCode, expectedObjectCode);
  CHECK_EQ(as.symbolTable(), expectedSymbolTable);
}
