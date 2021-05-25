#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "assembler/util.h"

TEST_CASE("rzp section data first") {
  std::map<std::string, int> symbolTable = {
    {"fat", 4},
    {"fim", 18},
    {"aux", 21},
    {"n", 22},
    {"one", 23},
  };

  std::vector<std::string> sourceFileContent = {
    "        section DATA",
    "aux:    space 1", // ERRO
    "n:      space",
    "one:    const 1",

    "        section TEXT",
    "        input n",
    "        load n",
    "fat:    sub one",
    "        jmpz", // ERRO
    "        store aux",
    "        mul n",
    "        store n n", //ERRO
    "        load aux",
    "        jmp fat",
    "fim:    output n",
    "        stop",
  };
}
