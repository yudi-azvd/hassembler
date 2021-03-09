#include <iostream>
#include <vector>
#include <map>

#include "../../lib/doctest/doctest.h"
#include "../../include/assembler.h"
#include "../../include/util.h"


TEST_CASE("sum of two numbers") {
  Assembler as;

  std::map<std::string, int> gotSymbolTable;
  std::map<std::string, int> expectedSymbolTable = {
    {"n1", 13},
    {"n2", 14},
    {"n3", 15},
  };

  std::vector<std::string> sourceFileContent = {
    "input n1",
    "input n2",
    "load n1",
    "add n2",
    "store n3",
    "output n3",
    "stop",
    "n1: space ",
    "n2: space ",
    "n3: space  ",
  };

  as.assemble(sourceFileContent);
  gotSymbolTable = as.symbolTable();

  INFO("got: ", strToIntMapToString(gotSymbolTable));
  INFO("exp: ", strToIntMapToString(expectedSymbolTable));
  CHECK_EQ(gotSymbolTable, expectedSymbolTable);
}


TEST_CASE("fatorial") {
  Assembler as;

  std::map<std::string, int> gotSymbolTable;
  std::map<std::string, int> expectedSymbolTable = {
    {"fat", 4},
    {"fim", 18},
    {"aux", 21},
    {"n", 22},
    {"one", 23},
  };

  std::vector<std::string> sourceFileContent = {
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
    "aux:    space",
    "n:      space",
    "one:    const 1",
  };

  as.assemble(sourceFileContent);
  gotSymbolTable = as.symbolTable();

  INFO("got: ", strToIntMapToString(gotSymbolTable));
  INFO("exp: ", strToIntMapToString(expectedSymbolTable));
  CHECK_EQ(gotSymbolTable, expectedSymbolTable);
}


TEST_CASE("fibonacci") {
  Assembler as;

  std::map<std::string, int> gotSymbolTable;
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
    "        copy zero,older",
    "        copy one, old",
    "        input limit",
    "        output old",
    "front:  load older",
    "        add old",
    "        store new",
    "        sub limit",
    "        jmpp final",
    "        output new",
    "        copy old, older",
    "        copy new, old",
    "        jmp front",
    "final:  output limit",
    "        stop",
    "zero:   const 0",
    "one:    const 1",
    "older:  space",
    "old:    space",
    "new:    space",
    "limit:  space",
  };

  as.assemble(sourceFileContent);
  gotSymbolTable = as.symbolTable();

  INFO("got: ", strToIntMapToString(gotSymbolTable));
  INFO("exp: ", strToIntMapToString(expectedSymbolTable));
  CHECK_EQ(gotSymbolTable, expectedSymbolTable);
}

TEST_CASE("area_triangulo") {

  Assembler as;

  std::map<std::string, int> gotSymbolTable;
  std::map<std::string, int> expectedSymbolTable = {
    {"b", 15},
    {"h", 16},
    {"r", 17},
    {"dois", 18},
  };

  std::vector<std::string> sourceFileContent = {
    "input b",
    "input h",
    "load b",
    "mul h",
    "div dois",
    "store r",
    "output r",
    "stop",
    "b: space",
    "h: space",
    "r: space",
    "dois: const 2",
  };

  as.assemble(sourceFileContent);
  gotSymbolTable = as.symbolTable();

  INFO("got: ", strToIntMapToString(gotSymbolTable));
  INFO("exp: ", strToIntMapToString(expectedSymbolTable));
  CHECK_EQ(gotSymbolTable, expectedSymbolTable);

}
