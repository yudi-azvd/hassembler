#include <iostream>
#include <vector>
#include <map>

#include "../../lib/doctest/doctest.h"
#include "../../include/assembler.h"
#include "../../include/util.h"


TEST_CASE("sum of two numbers") {
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

  Assembler as(sourceFileContent);

  as.runFirstPass();
  gotSymbolTable = as.symbolTable();

  INFO("got: ", strToIntMapToString(gotSymbolTable));
  INFO("exp: ", strToIntMapToString(expectedSymbolTable));
  CHECK_EQ(gotSymbolTable, expectedSymbolTable);
}


TEST_CASE("fatorial") {
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

  Assembler as(sourceFileContent);

  as.runFirstPass();
  gotSymbolTable = as.symbolTable();

  INFO("got: ", strToIntMapToString(gotSymbolTable));
  INFO("exp: ", strToIntMapToString(expectedSymbolTable));
  CHECK_EQ(gotSymbolTable, expectedSymbolTable);
}


TEST_CASE("fatorial with errors") {
  std::vector<std::string> sourceFileContent = {
    "        input n",
    "",
    "        load n",
    "fat:    sub one",
    "        jmpz fim",
    "        store aux",
    "        mul n",
    "",
    "        store n",
    "        load aux",
    "        jnp fat",
    "fim:    output n",
    "        stop",
    "a&uX:    space",
    "n:      space",
    "",
    "one:    const 1",
  };

  Assembler as(sourceFileContent);

  as.runFirstPass();

  std::vector<std::string> errors = as.errors();
  std::map<std::string, int> symbolTable = as.symbolTable();

  INFO("errors: ", vectorToString(errors));
  INFO("symbolTable: ", strToIntMapToString(as.symbolTable()));

  CHECK_EQ(2, errors.size());
  CHECK(findErrorWith("Erro Semântico, linha 11: instrução 'jnp' não identificada", errors));
  CHECK(findErrorWith("Erro Léxico, linha 14: símbolo 'a&uX' é inválido", errors));
}


TEST_CASE("fibonacci") {
  std::map<std::string, int> gotSymbolTable;
  std::map<std::string, int> expectedSymbolTable = {
    {"front", 10},
    {"final", 30},
    {"ZERO", 33},
    {"ONE", 34},
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
    "ZERO:   const 0",
    "ONE:    const 1",
    "older:  space",
    "old:    space",
    "new:    space",
    "limit:  space",
  };

  Assembler as(sourceFileContent);

  as.runFirstPass();
  gotSymbolTable = as.symbolTable();

  INFO("got: ", strToIntMapToString(gotSymbolTable));
  INFO("exp: ", strToIntMapToString(expectedSymbolTable));
  CHECK_EQ(gotSymbolTable, expectedSymbolTable);
}


TEST_CASE("area_triangulo") {
  std::map<std::string, int> gotSymbolTable;
  std::map<std::string, int> expectedSymbolTable = {
    {"B", 15},
    {"h", 16},
    {"r", 17},
    {"dois", 18},
  };

  std::vector<std::string> sourceFileContent = {
    "INPUT b",
    "INPUT H",
    "LOAD B",
    "MUL H",
    "DIV DOIS",
    "store r",
    "output r",
    "stop",
    "B: space",
    "h: space",
    "r: space",
    "dois: const 2",
  };


  Assembler as(sourceFileContent);

  as.runFirstPass();
  gotSymbolTable = as.symbolTable();

  INFO("got: ", strToIntMapToString(gotSymbolTable));
  INFO("exp: ", strToIntMapToString(expectedSymbolTable));
  CHECK_EQ(gotSymbolTable, expectedSymbolTable);
}


TEST_CASE("area_triangulo with label alone in line") {
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
    "b: ",
    // " space", // o que deveria acontecer nesse caso?
    "H: SPACE",
    "R: SPACE",
    "DOIS: CONST 2",
  };

  // A linha h: space tem dois rótulos. b: e h:. Professor disse que não 
  // ia ter esse casos?.

  Assembler as(sourceFileContent);

  as.runFirstPass();
  gotSymbolTable = as.symbolTable();

  INFO("got: ", strToIntMapToString(gotSymbolTable));
  INFO("exp: ", strToIntMapToString(expectedSymbolTable));
  CHECK_EQ(gotSymbolTable, expectedSymbolTable);
}


TEST_CASE("area_triangulo with errors") {
  std::vector<std::string> sourceFileContent = {
    "input b",
    "input h",
    "load b",
    "",
    "mult h",
    "divy dois",
    "store r",
    "output r",
    "stop",
    "1b: space",
    "h: space",
    "r: space",
    "",
    "r: space",
    "dois: konst 2",
  };

  Assembler as(sourceFileContent);

  as.runFirstPass();

  std::vector<std::string> errors = as.errors();
  std::map<std::string, int> symbolTable = as.symbolTable();

  INFO("errors: ", vectorToString(errors));
  INFO("symbolTable: ", strToIntMapToString(as.symbolTable()));

  // NOTAR QUE LINHAS EM BRANCO AINDA SÃO CONTADAS COMO LINHAS
  CHECK_EQ(5, errors.size());


  CHECK(findErrorWith("Erro Semântico, linha 5: instrução 'mult'", errors));
  CHECK(findErrorWith("Erro Semântico, linha 6: instrução 'divy'", errors));

  CHECK(findErrorWith("Erro Léxico, linha 10: símbolo '1b' é inválido", errors));
  CHECK_THROWS(symbolTable.at("1b")); // "1b" não deve ser incluído ta tabela de símbolos

  CHECK(findErrorWith("Erro Semântico, linha 14: símbolo 'r' redefinido", errors));
  CHECK(findErrorWith("Erro Semântico, linha 15: diretiva 'konst' não identificada", errors));
}
