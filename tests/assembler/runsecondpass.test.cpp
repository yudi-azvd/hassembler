#include <iostream>
#include <vector>

#include "../../lib/doctest/doctest.h"
#include "../../include/assembler.h"
#include "../../include/util.h"

TEST_CASE("rsp print number") {
  std::vector<std::string> sourceFileContent = {
    "input b",
    "output b",
    "B: SPACE",
  };

  std::map<std::string, int> symbolTable = {
    {"b", 4}
  };

  Assembler as(sourceFileContent);

  std::vector<int> gotObjectCode;
  std::vector<int> expectedObjectCode = {
    12, 4, 13, 4, 0
  };

  as.setSymbolTable(symbolTable);
  as.runSecondPass();
  gotObjectCode = as.objectCode();

  INFO("exp: ", vectorToString(expectedObjectCode));
  INFO("got: ", vectorToString(gotObjectCode));
  CHECK_EQ(gotObjectCode, expectedObjectCode);
}


TEST_CASE("rsp add two numbers") {
  std::vector<std::string> sourceFileContent = {
    "INPUT N1",
    "INPUT N2",
    "LOAD N1",
    "ADD N2",
    "STORE N3",
    "OUTPUT N3",
    "STOP",
    "N1: SPACE ; SPACE eh uma diretiva. uma funcao deve ser chamada ",
    "N2: SPACE ; e retornar uma nova posicao",
    "N3: SPACE",
  };

  std::map<std::string, int> symbolTable = {
    {"n1", 12},
    {"n2", 13},
    {"n3", 14},
  };

  Assembler as(sourceFileContent);

  std::vector<int> gotObjectCode;
  std::vector<int> expectedObjectCode = {
    12, 12, 12, 13, 10, 12, 1, 13, 11, 14, 13, 14, 14, 0, 0, 0
  };

  as.setSymbolTable(symbolTable);
  as.runSecondPass();
  gotObjectCode = as.objectCode();

  INFO("exp: ", vectorToString(expectedObjectCode));
  INFO("got: ", vectorToString(gotObjectCode));
  CHECK_EQ(gotObjectCode, expectedObjectCode);
}


TEST_CASE("rsp print and add number") {
  std::vector<std::string> sourceFileContent = {
    "input b",
    "add dois",
    "output b",
    "B: SPACE",
    "DOIS: const 2"
  };

  std::map<std::string, int> symbolTable = {
    {"b", 6},
    {"dois", 7},
  };

  Assembler as(sourceFileContent);

  std::vector<int> gotObjectCode;
  std::vector<int> expectedObjectCode = {
    12, 6, 1, 7, 13, 6, 0, 2
  };

  as.setSymbolTable(symbolTable);
  as.runSecondPass();
  gotObjectCode = as.objectCode();

  INFO("exp: ", vectorToString(expectedObjectCode));
  INFO("got: ", vectorToString(gotObjectCode));
  CHECK_EQ(gotObjectCode, expectedObjectCode);
}


TEST_CASE("rsp fibonacci") {
  std::map<std::string, int> symbolTable = {
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
    "ZERO:   CONST 0",
    "ONE:    CONST 1",
    "OLDER:  SPACE",
    "OLD:    SPACE",
    "NEW:    SPACE",
    "LIMIT:  SPACE",
  };

  Assembler as(sourceFileContent);

  std::vector<int> gotObjectCode;
  std::vector<int> expectedObjectCode = {
    9, 33, 35, 9, 34, 36, 12, 38, 13, 36, 10, 35, 1, 36, 11, 37, 2, 38, 7, 30, 13, 37, 9, 36, 35, 9, 37, 36, 5, 10, 13, 38, 14, 0, 1, 0, 0, 0, 0
  };

  as.setSymbolTable(symbolTable);
  as.runSecondPass();
  gotObjectCode = as.objectCode();

  INFO("exp: ", vectorToString(expectedObjectCode));
  INFO("got: ", vectorToString(gotObjectCode));
  CHECK_EQ(gotObjectCode, expectedObjectCode);
}


TEST_CASE("rsp fatorial") {
  std::map<std::string, int> symbolTable = {
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

  Assembler as(sourceFileContent);

  std::vector<int> gotObjectCode;
  std::vector<int> expectedObjectCode = {
    12, 22, 10, 22, 2, 23, 8, 18, 11, 21, 3, 22, 11, 22, 10, 21, 5, 4, 13, 22, 14, 0, 0, 1
  };

  as.setSymbolTable(symbolTable);
  as.runSecondPass();
  gotObjectCode = as.objectCode();

  INFO("exp: ", vectorToString(expectedObjectCode));
  INFO("got: ", vectorToString(gotObjectCode));
  CHECK_EQ(gotObjectCode, expectedObjectCode);
}