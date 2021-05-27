#include <iostream>

#include "assembler/assembler.h"


void showCorrectUsage();


int main(int commandlineCount, char* commandlineArguments[]) {
  std::vector<std::string> filenames;

  bool correctCommandlineArgumentsCount =
    2 <= commandlineCount && commandlineCount <= 4;
  if (!correctCommandlineArgumentsCount) {
    showCorrectUsage();
    return 1;
  }

  for (int i = 1; i < commandlineCount; i++) {
    filenames.push_back(commandlineArguments[i]);
  }

  Assembler assembler(filenames);

  assembler.assemble();

  return 0;
}


void showCorrectUsage() {
  std::cout <<
    "Informe o nome do arquivo fonte a ser montado. Exemplo:\n"
    "$ ./montador ./caminho/relativo/pro/seu/arquivo.asm"
  << std::endl;
}
