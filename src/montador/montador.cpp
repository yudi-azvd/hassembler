#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <map>

#include "../../include/assembler.h"


void showCorrectUsage();


int main(int commandlineCount, char* commandlineArguments[]) {
  if (commandlineCount <= 1) {
    showCorrectUsage();
    return 1;
  }

  Assembler assembler(commandlineArguments[1]);

  assembler.assemble();

  return 0;
}


void showCorrectUsage() {
  std::cout <<
    "Informe o nome do arquivo fonte a ser montado. Exemplo:\n" 
    "$ ./montador ./caminho/relativo/pro/seu/arquivo.asm" 
  << std::endl;
}
